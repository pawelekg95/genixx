#pragma once

#include "chromosome/Chromosome.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace genixx {

using Chromosomes = std::vector<std::shared_ptr<IChromosome>>;
using CrossingStrategy = std::function<Chromosomes(const Chromosomes&, const Chromosomes&)>;

class Individual
{
public:
    explicit Individual(std::uint32_t size)
        : m_chromosomes(size)
    {}

    explicit Individual(const Chromosomes& chromosomes)
        : m_chromosomes(chromosomes)
    {}

    void setCrossingStrategy(CrossingStrategy crossingStrategy) { m_crossingStrategy = crossingStrategy; }

    std::shared_ptr<IChromosome> chromosome(std::uint32_t index) { return m_chromosomes[index]; }

    Individual breed();

    Individual cross(const Individual& other);

    static float mutationProbability() { return m_mutationProbability; }

    static float mutationProbability(float probability)
    {
        m_mutationProbability = probability;
        return m_mutationProbability;
    }

private:
    Chromosomes m_chromosomes;
    static inline float m_mutationProbability{0.001};
    CrossingStrategy m_crossingStrategy;
};

} // namespace genixx
