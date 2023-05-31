#pragma once

#define _USE_MATH_DEFINES

#include "chromosome/Chromosome.h"
#include "population/Individual.h"

#include <memory>
#include <cmath>

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

static const genixx::CrossingStrategy cFirstStageChromosomeCrossingStrategy = [](const genixx::Chromosomes& chr1, const genixx::Chromosomes& chr2) -> genixx::Chromosomes {
    auto token = std::make_shared<FirstStageChromosome>(*dynamic_cast<FirstStageChromosome*>(chr1.at("x").get()));
    token->cross(*dynamic_cast<genixx::Chromosome<bool, double>*>(chr2.at("x").get()));
    return {{"x", token}};
};

static const std::function<double(genixx::Individual& individual)> cAssessmentFunction = [](genixx::Individual& individual) -> double {
    auto phenotype = dynamic_cast<FirstStageChromosome*>(individual.chromosome("x").get())->phenotype();
    return (std::exp(phenotype) * std::sin(M_PI * phenotype) + 1.0) / phenotype;
};
