#pragma once

#define _USE_MATH_DEFINES

#include "chromosome/Chromosome.h"
#include "population/Individual.h"

#include <cmath>
#include <iostream>
#include <memory>

class SecondStageChromosome : public genixx::Chromosome<bool, double>
{
public:
    SecondStageChromosome(const std::vector<bool>& genes, double domainBegin, double domainEnd)
        : genixx::Chromosome<bool, double>(genes)
        , m_domainBegin(domainBegin)
        , m_domainEnd(domainEnd)
    {}

    void mutate() override;

    double phenotype() override;

    std::shared_ptr<genixx::IChromosome> copy() override;

private:
    double m_domainBegin{};
    double m_domainEnd{};
};

std::shared_ptr<genixx::IChromosome> randomChromosome(double domainBegin, double domainEnd);

static const std::function<double(genixx::Individual& individual)> cAssessmentFunction =
    [](genixx::Individual& individual) -> double {
    auto x = dynamic_cast<SecondStageChromosome*>(individual.chromosome("x").get())->phenotype();
    auto y = dynamic_cast<SecondStageChromosome*>(individual.chromosome("y").get())->phenotype();

    auto token = 0.1 - std::sin(2 * x) - 0.2 * std::log10(std::sqrt(y));
    return token;
};
