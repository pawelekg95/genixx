#include "Chromosome.h"
#include "population/Individual.h"
#include "population/Population.h"
#include "population/selection/method.h"

#include <fmt/core.h>

#include <cstdint>
#include <iostream>
#include <fstream>

// Team: G1

static const std::uint32_t cGenerations = 100;
static const std::uint32_t cPopulationCount = 1000;
static const float cCrossingProbability = 0.5;
static const float cMutationProbability = 0.05;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    genixx::Individual::mutationProbability(cMutationProbability);

    // Creating new population consisting of individuals with specified chromosome crossing strategy
    genixx::Population population(cCrossingProbability);
    for (std::uint32_t individual = 0; individual < cPopulationCount; individual++)
    {
        auto ind = genixx::Individual({{"x", randomChromosome(1.0, 3.0)}, {"y", randomChromosome(0.0000000000001, 1.0)}});
        ind.setCrossingStrategy(cFirstStageChromosomeCrossingStrategy);
        population.populate(ind);
    }


    std::ofstream dataFile("data.csv");
    population.assessPopulation(cAssessmentFunction);
    std::cout << fmt::format("{:<28} {:<32} {:<36} {:<40}\n", "Generation", "Average score", "Best score", "Highest score phenotypes");
    std::cout << fmt::format("{:<28} {:<32} {:<36} {:<40}, {}\n",
                             population.generation(),
                             population.averageScore(),
                             population.bestScore(),
                             dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype(),
                             dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("y").get())->phenotype());
    dataFile << fmt::format("{},{},{},{},{}\n",
                            population.generation(),
                            population.averageScore(),
                            population.bestScore(),
                            dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype(),
                            dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("y").get())->phenotype());

    for (std::uint32_t generation = 0; generation < cGenerations - 1; generation++)
    {
        population = population.nextGeneration(genixx::selection::roulette);
        population.assessPopulation(cAssessmentFunction);
        std::cout << fmt::format("{:<28} {:<32} {:<36} {:<40}, {}\n",
                                 population.generation(),
                                 population.averageScore(),
                                 population.bestScore(),
                                 dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype(),
                                 dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("y").get())->phenotype());
        dataFile << fmt::format("{},{},{},{},{}\n",
                                population.generation(),
                                population.averageScore(),
                                population.bestScore(),
                                dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("x").get())->phenotype(),
                                dynamic_cast<SecondStageChromosome*>(population.bestIndividual().chromosome("y").get())->phenotype());
    }
    return 0;
}
