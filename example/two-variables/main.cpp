#include "Chromosome.h"
#include "genixx/population/Individual.h"
#include "genixx/population/Population.h"
#include "genixx/population/selection/method.h"

#include <fmt/core.h>

#include <cstdint>
#include <fstream>
#include <iostream>

static const std::uint32_t cGenerations = 50;
static const std::uint32_t cPopulationCount = 100;
static const float cCrossingProbability = 0.75;
static const float cMutationProbability = 0.005;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    genixx::config::assessmentThreads(10);
    genixx::Individual::mutationProbability(cMutationProbability);
    genixx::Population population(cCrossingProbability);
    for (std::uint32_t individual = 0; individual < cPopulationCount; individual++)
    {
        auto ind =
            genixx::Individual({{"x", randomChromosome(1.0, 3.0)}, {"y", randomChromosome(0.0000000000001, 1.0)}});
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
        dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype(),
        dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("y").get())->phenotype());

    for (std::uint32_t generation = 0; generation < cGenerations - 1; generation++)
    {
        population = population.nextGeneration(genixx::selection::ranking);
        population.assessPopulation(cAssessmentFunction);
        std::cout << fmt::format(
            "{:<28} {:<32} {:<36} {:<40} {}\n",
            population.generation(),
            population.averageScore(),
            population.bestScore(),
            dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype(),
            dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("y").get())->phenotype());
    }
    return 0;
}
