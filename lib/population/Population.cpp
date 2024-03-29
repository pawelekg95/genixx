#include "genixx/population/Population.h"

#include "genixx/error/exceptions.h"

#include <rethreadme/Thread.h>

#include <algorithm>
#include <chrono>
#include <functional>
#include <list>
#include <mutex>
#include <numeric>
#include <optional>
#include <semaphore>

namespace {

class Threads
{
public:
    static std::uint8_t size()
    {
        std::lock_guard lock(m_threadsAccessMtx);
        return m_availableThreads.size();
    }

    static std::uint8_t size(std::uint8_t threads)
    {
        std::lock_guard lock(m_threadsAccessMtx);
        if (m_availableThreads.size() < threads)
        {
            for (std::uint32_t i = threads - m_availableThreads.size(); i > 0; i--)
            {
                m_availableThreads.emplace_back(rethreadme::Thread<std::function<void()>>());
            }
        }
        else if (m_availableThreads.size() > threads)
        {
            while (m_availableThreads.size() > threads)
            {
                m_availableThreads.erase(m_availableThreads.end() - 1);
            }
        }
        return m_availableThreads.size();
    }

    static std::optional<rethreadme::Thread<std::function<void()>>*> getAvailableThread()
    {
        std::lock_guard lock(m_threadsAccessMtx);
        for (auto& thread : m_availableThreads)
        {
            if (thread.idle())
            {
                return &thread;
            }
        }
        return std::nullopt;
    }

private:
    static inline std::mutex m_threadsAccessMtx{};                                              // NOLINT
    static inline std::vector<rethreadme::Thread<std::function<void()>>> m_availableThreads{1}; // NOLINT
};

} // namespace

namespace genixx {
namespace config {

std::uint8_t assessmentThreads()
{
    return Threads::size();
}

std::uint8_t assessmentThreads(std::uint8_t threads)
{
    return Threads::size(threads);
}

} // namespace config

Population::Population(float crossingProbability)
    : m_crossingProbability(crossingProbability)
{
}

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
        if (static_cast<float>(randomPairs[i]) < m_crossingProbability * 100)
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

    std::uint32_t i = token.size() - 1;
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
    std::counting_semaphore<> doneAssessementSemaphore{0};
    auto assess = [&doneAssessementSemaphore, &assessmentFunction](IndividualInfo& individual) {
        individual.score = assessmentFunction(individual.individual);
        doneAssessementSemaphore.release();
    };
    for (auto& individual : m_individuals)
    {
        auto threadToExecute = Threads::getAvailableThread();
        while (!threadToExecute)
        {
            std::this_thread::sleep_for(10ms);
            threadToExecute = Threads::getAvailableThread();
        }
        threadToExecute.value()->queue(std::function<void()>([&assess, &individual]() { assess(individual); }));
    }

    for (std::uint32_t i = 0; i < m_individuals.size(); i++)
    {
        doneAssessementSemaphore.acquire();
    }
}

double Population::averageScore() const
{
    return std::accumulate(
               m_individuals.begin(),
               m_individuals.end(),
               0.0,
               [](double current, const IndividualInfo& individual) { return current += individual.score; }) /
           static_cast<double>(m_individuals.size());
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
