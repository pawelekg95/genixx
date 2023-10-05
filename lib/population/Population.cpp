#include "genixx/population/Population.h"

#include "genixx/error/exceptions.h"

#include <algorithm>
#include <chrono>
#include <mutex>
#include <numeric>
#include <thread>

namespace {

std::uint8_t threadsToAssess{1};

} // namespace

namespace genixx {
namespace config {

std::uint8_t assessmentThreads()
{
    return threadsToAssess;
}

std::uint8_t assessmentThreads(std::uint8_t threads)
{
    threadsToAssess = threads;
    return assessmentThreads();
}

} // namespace config

Population::Population(float crossingProbability)
    : m_crossingProbability(crossingProbability)
{}

Population Population::nextGeneration(const selection::SelectionMethod& selectionMethod) const
{
    if (m_individuals.empty())
    {
        throw WrongSizeException();
    }
    std::vector<Individual> individuals;
    std::vector<double> scores(m_individuals.size());
    for (std::uint32_t i = 0; i < m_individuals.size(); i++)
    {
        individuals.emplace_back(m_individuals[i].individual.copy());
        scores[i] = m_individuals[i].score;
    }

    auto selectedIndividuals = selectionMethod(individuals, scores);
    if (selectedIndividuals.size() > m_individuals.size())
    {
        throw WrongSizeException("More selected individuals than in population");
    }

    Population token;
    token.populate(!selectedIndividuals.empty() ? selectedIndividuals : [this]() -> std::vector<Individual> {
        std::vector<Individual> token;
        for (const auto& individual : m_individuals)
        {
            token.emplace_back(individual.individual);
        }
        return token;
    }());

    // Random pairs draw
    std::uint32_t pairsCount = token.size() / 2;
    std::vector<std::uint32_t> randomPairs(pairsCount);
    for (auto& pair : randomPairs)
    {
        pair = random(0, 100);
    }

    std::uint32_t current{};
    std::uint32_t next{current + 1};
    for (std::uint32_t i = 0; i < pairsCount; i++)
    {
        if (randomPairs[i] < m_crossingProbability * 100)
        {
            auto currentIndividual = token.m_individuals[current].individual;
            auto nextIndividual = token.m_individuals[next].individual;

            token.m_individuals[current].individual = currentIndividual.cross(nextIndividual);
            token.m_individuals[next].individual = nextIndividual.cross(currentIndividual);
        }
        current += 2;
        next += 2;
    }

    token.generationReplacement();

    std::int32_t i = token.size() - 1;
    while (token.size() < m_individuals.size())
    {
        token.populate(token.m_individuals[i].individual.breed());
        if (i > 0)
        {
            i--;
        }
        else
        {
            i = token.size() - 1;
        }
    }

    token.m_currentGeneration = m_currentGeneration + 1;

    return token;
}

void Population::generationReplacement()
{
    for (auto& [individual, _] : m_individuals)
    {
        individual = individual.breed();
    }
}

void Population::populate(const Individual& individual)
{
    m_individuals.emplace_back(IndividualInfo{individual});
}

void Population::populate(const std::vector<Individual>& individuals)
{
    for (const auto& individual : individuals)
    {
        m_individuals.emplace_back(IndividualInfo{individual});
    }
}

void Population::assessPopulation(const std::function<double(Individual& individual)>& assessmentFunction)
{
    if (!assessmentFunction)
    {
        throw NullFunctionException("Assessment function missing");
    }

    using namespace std::chrono_literals;
    std::mutex mtx{};
    std::uint8_t threadsAvailable{config::assessmentThreads()};
    std::uint64_t assessments = m_individuals.size();
    auto assess = [&mtx, &threadsAvailable, &assessmentFunction, &assessments](IndividualInfo& individual) {
        {
            std::lock_guard lock(mtx);
            threadsAvailable--;
        }
        individual.score = assessmentFunction(individual.individual);
        std::lock_guard lock(mtx);
        threadsAvailable++;
        assessments--;
    };
    for (auto& individual : m_individuals)
    {
        bool threadAvailable{};
        while (!threadAvailable)
        {
            std::this_thread::sleep_for(1ns);
            {
                std::lock_guard lock(mtx);
                threadAvailable = threadsAvailable > 0;
            }
        }
        {
            std::lock_guard lock(mtx);
            std::thread([&assess, &individual] { assess(individual); }).detach();
        }
    }
    // Clang tidy complains about condition not being updated inside the loop, however it is updated in detached
    // threads.
    while (assessments > 0) // NOLINT
    {
        std::this_thread::sleep_for(1ms);
    }
}

double Population::averageScore() const
{
    return std::accumulate(
               m_individuals.begin(),
               m_individuals.end(),
               0.0,
               [](double current, const IndividualInfo& individual) { return current += individual.score; }) /
           m_individuals.size();
}

double Population::bestScore() const
{
    return std::max_element(m_individuals.begin(),
                            m_individuals.end(),
                            [](const IndividualInfo& lhs, const IndividualInfo& rhs) { return lhs.score < rhs.score; })
        ->score;
}

Individual Population::bestIndividual() const
{
    return std::max_element(m_individuals.begin(),
                            m_individuals.end(),
                            [](const IndividualInfo& lhs, const IndividualInfo& rhs) { return lhs.score < rhs.score; })
        ->individual;
}

} // namespace genixx
