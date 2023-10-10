#pragma once

#include "genixx/population/Individual.h"
#include "genixx/population/selection/method.h"

#include <cstdint>
#include <vector>

namespace genixx {
namespace config {

std::uint8_t assessmentThreads();

std::uint8_t assessmentThreads(std::uint8_t threads);

} // namespace config

class Population
{
public:
    Population() = default;

    explicit Population(float crossingProbability);

    void populate(const Individual& individual);

    void populate(const std::vector<Individual>& individuals);

    std::uint32_t generation() const { return m_currentGeneration; }

    std::size_t population() const { return m_individuals.size(); }

    Population nextGeneration(const selection::SelectionMethod& selectionMethod = selection::roulette) const;

    void assessPopulation(const std::function<double(Individual& individual)>& assessmentFunction);

    double averageScore() const;

    double bestScore() const;

    Individual bestIndividual() const;

    std::uint32_t size() const { return m_individuals.size(); }

private:
    void generationReplacement();

private:
    struct IndividualInfo
    {
        Individual individual;
        double score{};
    };

    std::vector<IndividualInfo> m_individuals;
    std::uint32_t m_currentGeneration{1};
    float m_crossingProbability{1.0};
};

} // namespace genixx
