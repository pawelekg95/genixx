#pragma once

#include "genixx/error/exceptions.h"
#include "genixx/utils/random.h"

#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

namespace genixx {

class IChromosome
{
public:
    virtual ~IChromosome() = default;

    virtual void mutate() = 0;

    virtual std::size_t length() = 0;

    virtual std::shared_ptr<IChromosome> copy() = 0;

    virtual void cross(std::shared_ptr<IChromosome> other) = 0;

    virtual bool operator==(const IChromosome& other) const = 0;

    virtual bool operator!=(const IChromosome& other) const = 0;
};

template <typename Gene, typename Phenotype>
class Chromosome : public IChromosome
{
public:
    explicit Chromosome(const std::vector<Gene>& genes)
        : m_genes(genes)
    {
    }

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

    virtual Phenotype phenotype() = 0;

    std::size_t length() override { return m_genes.size(); }

protected:
    std::vector<Gene> m_genes;
};

} // namespace genixx
