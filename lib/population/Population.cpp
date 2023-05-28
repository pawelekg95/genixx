#include "population/Population.h"

#include "error/exceptions.h"

#include <algorithm>
#include <numeric>

namespace genixx {

Population::Population(const Parameters& parameters)
    : m_parameters(parameters)
{}

void Population::nextGeneration()
{}

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

void Population::assessPopulation(std::function<double(const Individual& individual)>& assessmentFunction)
{
    if (!assessmentFunction)
    {
        throw NullFunctionException();
    }

    for (auto& individual : m_individuals)
    {
        individual.score = assessmentFunction(individual.individual);
    }
}

double Population::avarageScore() const
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
