#include "genixx/chromosome/NumericChromosome.h"
#include "genixx/population/Individual.h"
#include "genixx/population/Population.h"
#include "genixx/population/selection/method.h"

#include <catch2/catch_all.hpp>

#include <cmath>
#include <cstdint>
#include <functional>

static const std::uint32_t cGenerations = 100;
static const std::uint32_t cPopulationCount = 1000;
static const float cCrossingProbability = 0.5;
static const float cMutationProbability = 0.3;
static const float cFunctionMaximum = 2.4;
static const float cFunctionMaximumX = 2.35619;
static const float cFunctionMaximumY = 0.0000000000001;
static const float cEpsilon = 0.0001;

// Assesment function calculates mathematical function written below.
// Genetic algorithm will aim to find the maximum for this function, for arguments range specified as chromosome range.
// Following wolfram alpha: https://tinyurl.com/nvuu4s5s the desired score (maximum) should be: 2,4 at point
// (phenotypes) (x: 2,35619, y: 0.0000000000001)
static const std::function<double(genixx::Individual& individual)> cAssessmentFunction =
    [](genixx::Individual& individual) -> double {
    auto x = dynamic_cast<genixx::NumericChromosome<double>*>(individual.chromosome("x").get())->phenotype();
    auto y = dynamic_cast<genixx::NumericChromosome<double>*>(individual.chromosome("y").get())->phenotype();

    auto token = 0.1 - std::sin(2 * x) - 0.2 * std::log10(std::sqrt(y));
    return token;
};

TEST_CASE("Two variables example as a test")
{
    genixx::config::assessmentThreads(10);
    genixx::Individual::mutationProbability(cMutationProbability);
    genixx::Population population(cCrossingProbability);
    for (std::uint32_t individual = 0; individual < cPopulationCount; individual++)
    {
        auto ind = genixx::Individual({{"x", genixx::NumericChromosome<double>::random(30, 1.0, 3.0)},
                                       {"y", genixx::NumericChromosome<double>::random(30, 0.0000000000001, 1.0)}});
        population.populate(ind);
    }

    for (std::uint32_t generation = 0; generation < cGenerations; generation++)
    {
        population = population.nextGeneration(genixx::selection::ranking);
        population.assessPopulation(cAssessmentFunction);
    }

    auto algorithmResult = population.bestScore();
    auto bestPhenotypeX =
        dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("x").get())
            ->phenotype();
    auto bestPhenotypeY =
        dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("y").get())
            ->phenotype();

    // Float comparison
    REQUIRE(std::abs(algorithmResult - cFunctionMaximum) < cEpsilon);
    REQUIRE(std::abs(bestPhenotypeX - cFunctionMaximumX) < cEpsilon);
    REQUIRE(std::abs(bestPhenotypeY - cFunctionMaximumY) < cEpsilon);
}
