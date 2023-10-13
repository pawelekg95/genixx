#include "genixx/chromosome/NumericChromosome.h"
#include "genixx/population/Individual.h"
#include "genixx/population/Population.h"
#include "genixx/population/selection/method.h"

#include <fmt/core.h>

#include <cstdint>
#include <fstream>
#include <iostream>

static const std::uint32_t cGenerations = 100;
static const std::uint32_t cPopulationCount = 1000;
static const float cCrossingProbability = 0.5;
static const float cMutationProbability = 0.3;


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

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
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

    population.assessPopulation(cAssessmentFunction);
    std::cout << fmt::format("{:<28} {:<32} {:<36} {:<40}\n",
                             "Generation",
                             "Average score",
                             "Best score",
                             "Highest score phenotypes");
    std::cout << fmt::format(
        "{:<28} {:<32} {:<36} {:<40} {}\n",
        population.generation(),
        population.averageScore(),
        population.bestScore(),
        dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("x").get())
            ->phenotype(),
        dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("y").get())
            ->phenotype());

    for (std::uint32_t generation = 0; generation < cGenerations - 1; generation++)
    {
        population = population.nextGeneration(genixx::selection::ranking);
        population.assessPopulation(cAssessmentFunction);
        std::cout << fmt::format(
            "{:<28} {:<32} {:<36} {:<40} {}\n",
            population.generation(),
            population.averageScore(),
            population.bestScore(),
            dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("x").get())
                ->phenotype(),
            dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("y").get())
                ->phenotype());
    }
    return 0;
}
