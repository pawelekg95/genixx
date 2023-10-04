#include "Chromosome.h"

#include "genixx/utils/random.h"

#include <cmath>

void FirstStageChromosome::mutate()
{
    auto mutationPlace = genixx::random(0, m_genes.size() - 1);
    m_genes[mutationPlace] = (1 - static_cast<std::int8_t>(m_genes[mutationPlace])) != 0;
}

double FirstStageChromosome::phenotype()
{
    std::uint32_t token{};
    for (std::uint32_t i = 0; i < m_genes.size(); i++)
    {
        if (m_genes[i])
        {
            token += std::pow(2, i);
        }
    }
    return 1.5 + (3.5 - 1.5) * token / std::pow(2, m_genes.size());
}

std::shared_ptr<genixx::IChromosome> randomChromosome()
{
    std::vector<bool> genes(11);
    for (std::uint32_t i = 0; i < 11; i++)
    {
        genes[i] = static_cast<bool>(genixx::random(0, 1));
    }
    return std::make_shared<FirstStageChromosome>(genes);
}

std::shared_ptr<genixx::IChromosome> FirstStageChromosome::copy()
{
    return std::make_shared<FirstStageChromosome>(m_genes);
}
