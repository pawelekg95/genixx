#include "Chromosome.h"
#include "utils/random.h"

#include <cmath>

void SecondStageChromosome::mutate()
{
    auto mutationPlace = genixx::random(0, m_genes.size());
    m_genes[mutationPlace] = (1 - static_cast<std::int8_t>(m_genes[mutationPlace])) != 0;
}

double SecondStageChromosome::phenotype()
{
    std::uint32_t token{};
    for (std::uint32_t i = 0; i < m_genes.size(); i++)
    {
        if (m_genes[i])
        {
            token += std::pow(2, i);
        }
    }
    return m_domainBegin + (m_domainEnd - m_domainBegin) * token / std::pow(2, m_genes.size());
}

std::shared_ptr<genixx::IChromosome> randomChromosome(double domainBegin, double domainEnd)
{
    std::vector<bool> genes(11);
    for (std::uint32_t i = 0; i < 11; i++)
    {
        genes[i] = static_cast<bool>(genixx::random(0, 1));
    }
    return std::make_shared<SecondStageChromosome>(genes, domainBegin, domainEnd);
}

std::shared_ptr<genixx::IChromosome> SecondStageChromosome::copy()
{
    return std::make_shared<SecondStageChromosome>(m_genes, m_domainBegin, m_domainEnd);
}
