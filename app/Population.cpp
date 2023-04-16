#include "Population.h"

#include "tools.h"

#include <algorithm>
#include <numeric>

Population::Population(parameters::Parameters parameters)
    : m_parameters(parameters)
    , m_population(m_parameters.population)

{
    for (auto& individual : m_population)
    {
        for (std::uint32_t i = 0; i < individual.genes.size(); i++)
        {
            individual.genes[i] = static_cast<bool>(random(0, 1));
        }
    }
}

void Population::calculatePhenotypes()
{
    for (std::uint32_t i = 0; i < m_parameters.population; i++)
    {
        m_population[i].phenotype =
            m_parameters.searchingAreaBegin + (m_parameters.searchingAreaEnd - m_parameters.searchingAreaBegin) *
                                                  phenotype(i) / std::pow(2, parameters::cGenes);
    }
}

void Population::checkCorrectness()
{
    for (auto& individual : m_population)
    {
        auto phenotype = individual.phenotype;
        individual.fit = (std::exp(phenotype) * std::sin(pi * phenotype) + 1.0) / phenotype;
    }
}

void Population::roulette()
{
    std::vector<Chromosome> newGeneration(m_parameters.population);
    std::vector<double> matrixNi(m_parameters.population);
    normalize();
    double fitSum = std::accumulate(m_population.begin(),
                                    m_population.end(),
                                    0.0,
                                    [](const double& init, const Chromosome& obj) -> double { return init + obj.fit; });

    for (std::uint32_t i = 0; i < matrixNi.size(); i++)
    {
        matrixNi[i] = m_population[i].fit / fitSum * std::pow(2, parameters::cGenes);
    }

    std::vector<std::uint32_t> randoms(m_parameters.population);

    for (auto& num : randoms)
    {
        num = random(0, std::pow(2.0, static_cast<double>(parameters::cGenes)));
    }

    std::vector<double> rouletteToken(m_parameters.population);
    double position{};
    for (std::uint32_t i = 0; i < m_parameters.population; i++)
    {
        position += matrixNi[i];
        rouletteToken[i] = position;
    }

    for (std::uint32_t i = 0; i < m_parameters.population; i++)
    {
        std::uint32_t j{};
        while (randoms[i] > rouletteToken[++j] && j < rouletteToken.size())
            ;
        for (std::uint32_t k = 0; k < parameters::cGenes; k++)
        {
            newGeneration[i].genes[k] = m_population[j].genes[k];
        }
    }
    m_population = newGeneration;
}

void Population::crossing()
{
    std::uint32_t pairsCount = m_parameters.population / 2;
    std::vector<std::uint32_t> randomPairs(pairsCount);
    for (auto& pair : randomPairs)
    {
        pair = random(0, 100);
    }

    std::vector<std::uint32_t> randomPlaces(pairsCount);
    for (auto& place : randomPlaces)
    {
        place = random(0, parameters::cGenes - 2);
    }

    std::uint32_t first{};
    bool buffer{};
    for (std::uint32_t i = 0; i < pairsCount; i++)
    {
        if (randomPairs[i] < m_parameters.crossingProbability * 100)
        {
            for (std::uint32_t j = randomPlaces[i]; j < parameters::cGenes - 1; j++)
            {
                buffer = m_population[first].genes[i];
                m_population[first].genes[i] = m_population[first + 1].genes[i];
                m_population[first + 1].genes[i] = buffer;
            }
        }
        first += 2;
    }
}

void Population::mutate()
{
    std::vector<double> randoms(m_parameters.population);
    for (auto& num : randoms)
    {
        num = random(0, 100) / 100.0;
    }

    std::uint32_t mutationPlace{};
    for (std::uint32_t i = 0; i < m_parameters.population; i++)
    {
        if (randoms[i] < m_parameters.mutationProbability)
        {
            mutationPlace = random(0, parameters::cGenes);
            m_population[i].genes[mutationPlace] =
                (1 - static_cast<std::int8_t>(m_population[i].genes[mutationPlace])) != 0;
        }
    }
}

[[maybe_unused]] std::vector<double> Population::populationPhenotypes() const
{
    std::vector<double> token;
    for (const auto& individual : m_population)
    {
        token.emplace_back(individual.phenotype);
    }
    return token;
}

[[maybe_unused]] std::vector<double> Population::populationCorrectness() const
{
    std::vector<double> token;
    for (const auto& individual : m_population)
    {
        token.emplace_back(individual.fit);
    }
    return token;
}

[[maybe_unused]] std::vector<std::string> Population::populationChromosomes() const
{
    std::vector<std::string> token;
    for (const auto& individual : m_population)
    {
        token.emplace_back(individual.genes.to_string());
    }
    return token;
}

double Population::averageCorrectness() const
{
    return std::accumulate(m_population.begin(),
                           m_population.end(),
                           0.0,
                           [](const double& init, const Chromosome& chromosome) { return init + chromosome.fit; }) /
           static_cast<double>(m_population.size());
}

double Population::maxCorrectness() const
{
    return std::max_element(m_population.begin(),
                            m_population.end(),
                            [](const Chromosome& lhs, const Chromosome& rhs) { return lhs.fit < rhs.fit; })
        ->fit;
}

std::uint32_t Population::phenotype(std::uint32_t individual) const
{
    return m_population[individual].genes.to_ulong();
}

void Population::normalize()
{
    double min =
        std::min_element(m_population.begin(), m_population.end(), [](const Chromosome& lhs, const Chromosome& rhs) {
            return lhs.fit < rhs.fit;
        })->fit;
    double max =
        std::max_element(m_population.begin(), m_population.end(), [](const Chromosome& lhs, const Chromosome& rhs) {
            return lhs.fit < rhs.fit;
        })->fit;
    double offset = (max - min) / (parameters::cGenes - 1) - min;
    for (auto& individual : m_population)
    {
        individual.fit += offset;
    }
}
