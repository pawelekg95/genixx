#include "genixx/population/Individual.h"

#include "genixx/error/exceptions.h"
#include "genixx/utils/random.h"

#include <fmt/core.h>

#include <iostream>
#include <utility>

namespace genixx {

Individual::Individual(const Individual& other)
{
    *this = other.copy();
}

Individual::Individual(Individual&& other) noexcept
    : m_chromosomes(std::move(other.m_chromosomes))
{}

Individual& Individual::operator=(const Individual& other)
{
    if (&other == this)
    {
        return *this;
    }
    *this = other.copy();
    return *this;
}

Individual& Individual::operator=(Individual&& other) noexcept
{
    if (&other == this)
    {
        return *this;
    }
    m_chromosomes = std::move(other.m_chromosomes);
    return *this;
}

Individual Individual::breed() const
{
    auto next = copy();
    for (auto& [id, chromosome] : next.m_chromosomes)
    {
        auto shouldMutate = (random(0.0, 100.0) / 100.0) <= m_mutationProbability;
        if (shouldMutate)
        {
            chromosome->mutate();
        }
    }
    return next;
}

Individual Individual::cross(const Individual& other)
{
    if (m_chromosomes.size() != other.m_chromosomes.size())
    {
        throw WrongSizeException("Incorrect amount of chromosomes in individuals");
    }
    auto newChromosomes = Chromosomes();
    for (auto& [id, chromosome] : m_chromosomes)
    {
        auto chromosomeToChross = other.m_chromosomes.find(id);
        if (chromosomeToChross == other.m_chromosomes.end())
        {
            throw InvalidArgumentException(
                fmt::format("Chromosome mismatch. Cannot find chromosome: {} in second individual", id));
        }
        auto newChromosome = chromosome->copy();
        newChromosome->cross(chromosomeToChross->second);
        newChromosomes[id] = newChromosome;
    }
    return Individual(newChromosomes);
}

Individual Individual::copy() const
{
    Chromosomes chromosomes;
    for (const auto& [id, chromosome] : m_chromosomes)
    {
        chromosomes[id] = chromosome->copy();
    }
    return Individual(chromosomes);
}

bool Individual::operator==(const Individual& other) const
{
    if (m_chromosomes.size() != other.m_chromosomes.size())
    {
        return false;
    }
    for (const auto& [id, chromosome] : m_chromosomes)
    {
        if (other.m_chromosomes.find(id) == other.m_chromosomes.end())
        {
            return false;
        }
        if (*chromosome != *other.m_chromosomes.at(id))
        {
            return false;
        }
    }
    return true;
}

bool Individual::operator!=(const Individual& other) const
{
    return !(*this == other);
}

} // namespace genixx
