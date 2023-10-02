#include "Chromosome.h"
#include "genixx/population/Individual.h"
#include "genixx/population/Population.h"
#include "genixx/population/selection/method.h"

#include <fmt/core.h>

#include <cstdint>
#include <iostream>

// Team: G1

static const std::uint32_t cGenerations = 100;
static const std::uint32_t cPopulationCount = 1000;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Creating new population consisting of individuals with specified chromosome crossing strategy
    genixx::Population population;
    for (std::uint32_t individual = 0; individual < cPopulationCount; individual++)
    {
        auto ind = genixx::Individual({{"x", randomChromosome()}});
        population.populate(ind);
    }

    population.assessPopulation(cAssessmentFunction);
    std::cout << fmt::format("{:<28} {:<32} {:<36} {:<40}\n",
                             "Generation",
                             "Average score",
                             "Best score",
                             "Highest score phenotype");
    std::cout << fmt::format(
        "{:<28} {:<32} {:<36} {:<40}\n",
        population.generation(),
        population.averageScore(),
        population.bestScore(),
        dynamic_cast<FirstStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype());

    for (std::uint32_t generation = 0; generation <= cGenerations; generation++)
    {
        population = population.nextGeneration(genixx::selection::roulette);
        population.assessPopulation(cAssessmentFunction);
        std::cout << fmt::format(
            "{:<28} {:<32} {:<36} {:<40}\n",
            population.generation(),
            population.averageScore(),
            population.bestScore(),
            dynamic_cast<FirstStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype());
    }
    return 0;
}
