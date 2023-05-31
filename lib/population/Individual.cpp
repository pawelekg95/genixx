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
    , m_crossingStrategy(std::move(other.m_crossingStrategy))
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
    m_crossingStrategy = std::move(other.m_crossingStrategy);
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
    if (!m_crossingStrategy)
    {
        throw NullFunctionException();
    }
    Individual ret(m_crossingStrategy(m_chromosomes, other.m_chromosomes));
    ret.setCrossingStrategy(m_crossingStrategy);
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
    ret.setCrossingStrategy(m_crossingStrategy);
    return ret;
}

} // namespace genixx
