#include "genixx/chromosome/NumericChromosome.h"
#include "genixx/population/Individual.h"
#include "genixx/population/Population.h"
#include "genixx/population/selection/method.h"

#include <fmt/core.h>

#include <cstdint>
#include <iostream>

// Team: G1

static const std::uint32_t cGenerations = 40;
static const std::uint32_t cPopulationCount = 100;

static const std::function<double(genixx::Individual& individual)> cAssessmentFunction =
    [](genixx::Individual& individual) -> double {
    auto phenotype = static_cast<genixx::NumericChromosome<double>*>(individual.chromosome("x").get())->phenotype();
    return (std::exp(phenotype) * std::sin(M_PI * phenotype) + 1.0) / phenotype;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Creating new population consisting of individuals with specified chromosome crossing strategy
    genixx::Population population;
    for (std::uint32_t individual = 0; individual < cPopulationCount; individual++)
    {
        auto ind = genixx::Individual({{"x", genixx::NumericChromosome<double>::random(11, 1.5, 3.5)}});
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
        static_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("x").get())->phenotype());

    for (std::uint32_t generation = 0; generation <= cGenerations; generation++)
    {
        population = population.nextGeneration(genixx::selection::roulette);
        population.assessPopulation(cAssessmentFunction);
        std::cout << fmt::format(
            "{:<28} {:<32} {:<36} {:<40}\n",
            population.generation(),
            population.averageScore(),
            population.bestScore(),
            static_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("x").get())->phenotype());
    }
    return 0;
}
