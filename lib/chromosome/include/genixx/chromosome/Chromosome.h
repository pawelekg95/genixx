#pragma once

#include "genixx/error/exceptions.h"
#include "genixx/utils/random.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace genixx {

class IChromosome
{
public:
    virtual ~IChromosome() = default;

    virtual void mutate() = 0;

    virtual std::uint32_t length() = 0;

    virtual std::shared_ptr<IChromosome> copy() = 0;

    virtual void cross(std::shared_ptr<IChromosome> other) = 0;
};

template <typename Gene, typename Phenotype>
class Chromosome : public IChromosome
{
public:
    explicit Chromosome(const std::vector<Gene>& genes)
        : m_genes(genes)
    {}

    virtual Phenotype phenotype() = 0;

    void cross(std::shared_ptr<IChromosome> other) override
    {
        auto otherGenes = static_cast<Chromosome<Gene, Phenotype>*>(other.get())->m_genes;
        if (m_genes.size() != otherGenes.size())
        {
            throw genixx::WrongSizeException();
        }
        auto crossingPoint = genixx::random(0, m_genes.size() - 1);
        for (std::uint32_t i = crossingPoint; i < otherGenes.size(); i++)
        {
            m_genes[i] = otherGenes[i];
        }
    }

    std::uint32_t length() override { return m_genes.size(); }

protected:
    // Having ordinary container instead of std::bitset due to its template limitations - size cannot be variadic.
    std::vector<Gene> m_genes;
};

} // namespace genixx
