#include "population/Individual.h"

#include "error/exceptions.h"
#include "utils/random.h"

namespace genixx {

Individual Individual::breed()
{
    Individual next{*this};
    for (auto& chromosome : next.m_chromosomes)
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
    return Individual(m_crossingStrategy(m_chromosomes, other.m_chromosomes));
}

} // namespace genixx
