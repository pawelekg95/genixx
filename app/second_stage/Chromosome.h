#pragma once

#define _USE_MATH_DEFINES

#include "chromosome/Chromosome.h"
#include "population/Individual.h"

#include <memory>
#include <cmath>
#include <iostream>

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

static const genixx::CrossingStrategy cFirstStageChromosomeCrossingStrategy = [](const genixx::Chromosomes& chr1, const genixx::Chromosomes& chr2) -> genixx::Chromosomes {
    auto chr1FirstChromosome = std::make_shared<SecondStageChromosome>(*dynamic_cast<SecondStageChromosome*>(chr1.at("x").get()));
    auto chr2FirstChromosome = std::make_shared<SecondStageChromosome>(*dynamic_cast<SecondStageChromosome*>(chr2.at("x").get()));

    auto chr1SecondChromosome = std::make_shared<SecondStageChromosome>(*dynamic_cast<SecondStageChromosome*>(chr1.at("y").get()));
    auto chr2SecondChromosome = std::make_shared<SecondStageChromosome>(*dynamic_cast<SecondStageChromosome*>(chr2.at("y").get()));

    chr1FirstChromosome->cross(*chr2FirstChromosome);
    chr1SecondChromosome->cross(*chr2SecondChromosome);
    return genixx::Chromosomes{{"x", chr1FirstChromosome}, {"y", chr1SecondChromosome}};
};

static const std::function<double(genixx::Individual& individual)> cAssessmentFunction = [](genixx::Individual& individual) -> double {
    auto x = dynamic_cast<SecondStageChromosome*>(individual.chromosome("x").get())->phenotype();
    auto y = dynamic_cast<SecondStageChromosome*>(individual.chromosome("y").get())->phenotype();

    auto token = 0.1 - std::sin(2 * x) - 0.2 * std::log10(std::sqrt(y));
    return token;
};
