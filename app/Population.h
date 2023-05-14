#pragma once

#include "parameters.h"

#include <bitset>
#include <cstdint>
#include <vector>

class Population
{
public:
    explicit Population(parameters::Parameters parameters);

    void calculatePhenotypes();

    void checkCorrectness();

    void roulette();

    void crossing();

    void mutate();

    [[maybe_unused]] std::vector<double> populationPhenotypes() const;

    [[maybe_unused]] std::vector<double> populationCorrectness() const;

    [[maybe_unused]] std::vector<std::string> populationChromosomes() const;

    double averageCorrectness() const;

    double maxCorrectness() const;

    double maxCorrectnessPhenotype() const;

private:
    struct Chromosome
    {
        std::bitset<parameters::cGenes> genes;
        double phenotype{};
        double fit{};
    };

    std::uint32_t phenotype(std::uint32_t individual) const;

    void normalize();

private:
    parameters::Parameters m_parameters;
    std::vector<Chromosome> m_population;
};
