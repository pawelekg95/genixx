#pragma once

#include "error/exceptions.h"
#include "utils/random.h"

#include <cstdint>
#include <vector>

namespace genixx {

class IChromosome
{
public:
    virtual void mutate() = 0;
};

template <typename Gene, typename Phenotype>
class Chromosome : public IChromosome
{
public:
    explicit Chromosome(std::uint32_t size)
        : m_genes(size)
    {}

    explicit Chromosome(const std::vector<Gene>& genes)
        : m_genes(genes)
    {}

    virtual Phenotype phenotype() = 0;

    virtual void cross(const Chromosome<Gene, Phenotype>& other) = 0;

    std::vector<Gene> genes() const { return m_genes; }

protected:
    // Having ordinary container instead of std::bitset due to it's template limitations - size cannot be variadic.
    std::vector<Gene> m_genes;
};

} // namespace genixx
