#pragma once

#define _USE_MATH_DEFINES

#include "genixx/chromosome/Chromosome.h"
#include "genixx/population/Individual.h"

#include <cmath>
#include <memory>

class FirstStageChromosome : public genixx::Chromosome<bool, double>
{
public:
    FirstStageChromosome(const std::vector<bool>& genes)
        : genixx::Chromosome<bool, double>(genes)
    {}

    void mutate() override;

    double phenotype() override;

    std::shared_ptr<genixx::IChromosome> copy() override;
};

std::shared_ptr<genixx::IChromosome> randomChromosome();

static const std::function<double(genixx::Individual& individual)> cAssessmentFunction =
    [](genixx::Individual& individual) -> double {
    auto phenotype = dynamic_cast<FirstStageChromosome*>(individual.chromosome("x").get())->phenotype();
    return (std::exp(phenotype) * std::sin(M_PI * phenotype) + 1.0) / phenotype;
};
