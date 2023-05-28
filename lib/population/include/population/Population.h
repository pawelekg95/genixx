#pragma once

#include "population/Individual.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace genixx {

struct Parameters
{
    double crossingProbability{};
};

const Parameters cDefaults = {1.0};

class Population
{
public:
    Population();

    explicit Population(const Parameters& parameters);

    void populate(const Individual& individual);

    void populate(const std::vector<Individual>& individuals);

    std::uint32_t generation() const { return m_currentGeneration; }

    std::uint32_t population() const { return m_individuals.size(); }

    void nextGeneration();

    void assessPopulation(std::function<double(const Individual& individual)>& assessmentFunction);

    double avarageScore() const;

    double bestScore() const;

    Individual bestIndividual() const;

private:
    struct IndividualInfo
    {
        Individual individual;
        double score{};
    };

    Parameters m_parameters{cDefaults};
    std::vector<IndividualInfo> m_individuals;
    std::uint32_t m_currentGeneration{};
};

} // namespace genixx
