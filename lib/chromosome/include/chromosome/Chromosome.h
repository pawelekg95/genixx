#pragma once

#include "error/exceptions.h"
#include "utils/random.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace genixx {

class IChromosome
{
public:
    ~IChromosome() = default;

    virtual void mutate() = 0;

    virtual std::uint32_t genes() = 0;

    virtual std::shared_ptr<IChromosome> copy() = 0;
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

    virtual void cross(const Chromosome<Gene, Phenotype>& other)
    {
        auto otherGenes = other.m_genes;
        if (m_genes.size() != otherGenes.size())
        {
            throw genixx::WrongSizeException();
        }
        auto crossingPoint = genixx::random(0, m_genes.size());
        for (std::uint32_t i = crossingPoint; i < otherGenes.size(); i++)
        {
            m_genes[i] = otherGenes[i];
        }
    }

    std::uint32_t genes() override { return m_genes.size(); }

protected:
    // Having ordinary container instead of std::bitset due to its template limitations - size cannot be variadic.
    std::vector<Gene> m_genes;
};

} // namespace genixx
