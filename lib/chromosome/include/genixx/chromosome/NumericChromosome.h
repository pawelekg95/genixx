#pragma once

#include "genixx/chromosome/Chromosome.h"
#include "genixx/utils/random.h"

#include <type_traits>
#include <limits>
#include <cstdint>

namespace genixx {

template <typename Numeric, typename = std::enable_if_t<std::is_arithmetic_v<Numeric>>>
class NumericChromosome : public Chromosome<bool, Numeric>
{
public:
    NumericChromosome(const std::vector<bool>& genes,
                     Numeric min = std::numeric_limits<Numeric>::min(),
                     Numeric max = std::numeric_limits<Numeric>::max())
        : genixx::Chromosome<bool, Numeric>(genes)
        , m_min(min)
        , m_max(max)
    {}

    void mutate() override
    {
        auto mutationPlace = genixx::random(0, this->m_genes.size() - 1);
        this->m_genes[mutationPlace] = (1 - static_cast<std::int8_t>(this->m_genes[mutationPlace])) != 0;
    }

    Numeric phenotype() override
    {
        Numeric token{};
        for (std::uint32_t i = 0; i < this->m_genes.size(); i++)
        {
            if (this->m_genes[i])
            {
                token += std::pow(2, i);
            }
        }
        return m_min + (m_max - m_min) * token / std::pow(2, this->m_genes.size());
    }

    std::shared_ptr<IChromosome> copy() override
    {
        return std::make_shared<NumericChromosome<Numeric>>(this->m_genes, this->m_min, this->m_max);
    }

    static std::shared_ptr<NumericChromosome<Numeric>> random(std::uint32_t length, Numeric min = std::numeric_limits<Numeric>::min(),
                     Numeric max = std::numeric_limits<Numeric>::max())
    {
        std::vector<bool> genes(length);
        for (std::uint32_t i = 0; i < length; i++)
        {
            genes[i] = static_cast<bool>(genixx::random(0, 1));
        }
        return std::make_shared<NumericChromosome<Numeric>>(genes, min, max);
    }

private:
    Numeric m_min{};
    Numeric m_max{};
};


} // namespace genixx
