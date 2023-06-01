#include "population/Individual.h"

#include "error/exceptions.h"
#include "utils/random.h"

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
        auto shouldMutate = (random(0, 100) / 100.0) <= m_mutationProbability;
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
        auto newChromosome = chromosome->copy();
        newChromosome->cross(other.m_chromosomes.at(id));
        newChromosomes[id] = newChromosome;
    }
    Individual ret(newChromosomes);
    return ret;
}

Individual Individual::copy() const
{
    Chromosomes chromosomes;
    for (const auto& [id, chromosome] : m_chromosomes)
    {
        chromosomes[id] = chromosome->copy();
    }
    Individual ret(chromosomes);
    return ret;
}

} // namespace genixx
