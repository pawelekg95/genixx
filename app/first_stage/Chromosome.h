#pragma once

#include "chromosome/Chromosome.h"
#include "population/Individual.h"

class FirstStageChromosome : public genixx::Chromosome<bool, double>
{
public:
    FirstStageChromosome(const std::vector<bool>& genes)
        : genixx::Chromosome<bool, double>(genes)
    {}

    void mutate() override;

    double phenotype() override;

    void cross(const genixx::Chromosome<bool, double>& other) override;
};

FirstStageChromosome randomChromosome();

static const genixx::CrossingStrategy cFirstStageChromosomeCrossingStrategy = [](const genixx::Chromosomes& chr1, const genixx::Chromosomes& chr2) -> genixx::Chromosomes {
    auto token = std::make_shared<FirstStageChromosome>(*dynamic_cast<FirstStageChromosome*>(chr1[0].get()));
    token->cross(*dynamic_cast<genixx::Chromosome<bool, double>*>(chr2[0].get()));
    return {token};
};
