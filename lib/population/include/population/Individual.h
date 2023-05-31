#pragma once

#include "chromosome/Chromosome.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <map>
#include <vector>
#include <utility>
#include <string>

namespace genixx {

using Chromosomes = std::map<std::string, std::shared_ptr<IChromosome>>;
using CrossingStrategy = std::function<Chromosomes(const Chromosomes&, const Chromosomes&)>;

class Individual
{
public:
    explicit Individual(const Chromosomes& chromosomes)
        : m_chromosomes(chromosomes)
    {}

    Individual(const Individual& other);

    Individual(Individual&& other) noexcept;

    Individual& operator=(const Individual& other);

    Individual& operator=(Individual&& other) noexcept;

    void setCrossingStrategy(CrossingStrategy crossingStrategy) { m_crossingStrategy = std::move(crossingStrategy); }

    std::shared_ptr<IChromosome> chromosome(const std::string& id) { return m_chromosomes[id]; }

    Individual copy() const;

    Individual breed() const;

    Individual cross(const Individual& other);

    static float mutationProbability() { return m_mutationProbability; }

    static float mutationProbability(float probability)
    {
        m_mutationProbability = probability;
        return m_mutationProbability;
    }

private:
    Chromosomes m_chromosomes;
    CrossingStrategy m_crossingStrategy;
    static inline float m_mutationProbability{0.001};
};

} // namespace genixx
