#include "Chromosome.h"
#include "error/exceptions.h"
#include "utils/random.h"

#include <cmath>

void FirstStageChromosome::mutate()
{
    auto mutationPlace = genixx::random(0, m_genes.size());
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

void FirstStageChromosome::cross(const genixx::Chromosome<bool, double>& other)
{
    auto otherGenes = other.genes();
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

FirstStageChromosome randomChromosome()
{
    std::vector<bool> genes(11);
    for (std::uint32_t i = 0; i < 11; i++)
    {
        genes[i] = static_cast<bool>(genixx::random(0, 1));
    }
    return genes;
}
