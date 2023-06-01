#pragma once

#include "chromosome/Chromosome.h"

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace genixx {

using Chromosomes = std::map<std::string, std::shared_ptr<IChromosome>>;

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

    ~Individual() = default;

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
    static inline float m_mutationProbability{0.001};
};

} // namespace genixx
