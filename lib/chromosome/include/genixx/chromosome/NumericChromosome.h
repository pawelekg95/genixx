#pragma once

#include "genixx/chromosome/Chromosome.h"
#include "genixx/utils/random.h"

#include <cstdint>
#include <limits>
#include <type_traits>

namespace genixx {

template <typename Numeric, typename = std::enable_if_t<std::is_arithmetic_v<Numeric>>>
class NumericChromosome : public Chromosome<bool, Numeric>
{
public:
    NumericChromosome(const std::vector<bool>& genes,
                      Numeric min = std::numeric_limits<Numeric>::min(),
                      Numeric max = std::numeric_limits<Numeric>::max())
        : Chromosome<bool, Numeric>(genes)
        , m_min(min)
        , m_max(max)
    {}

    void mutate() override
    {
        auto mutationPlace = genixx::random(0, Chromosome<bool, Numeric>::m_genes.size() - 1);
        Chromosome<bool, Numeric>::m_genes[mutationPlace] =
            (1 - static_cast<std::int8_t>(Chromosome<bool, Numeric>::m_genes[mutationPlace])) != 0;
    }

    Numeric phenotype() override
    {
        Numeric token{};
        for (std::uint32_t i = 0; i < Chromosome<bool, Numeric>::m_genes.size(); i++)
        {
            if (Chromosome<bool, Numeric>::m_genes[i])
            {
                token += std::pow(2, i);
            }
        }
        return m_min + (m_max - m_min) * token / std::pow(2, Chromosome<bool, Numeric>::m_genes.size());
    }

    std::shared_ptr<IChromosome> copy() override
    {
        return std::make_shared<NumericChromosome<Numeric>>(Chromosome<bool, Numeric>::m_genes, m_min, m_max);
    }

    static std::shared_ptr<NumericChromosome<Numeric>> random(std::uint32_t length,
                                                              Numeric min = std::numeric_limits<Numeric>::min(),
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
