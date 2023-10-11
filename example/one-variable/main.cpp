#include "genixx/chromosome/NumericChromosome.h"
#include "genixx/population/Individual.h"
#include "genixx/population/Population.h"
#include "genixx/population/selection/method.h"

#include <fmt/core.h>

#include <cstdint>
#include <iostream>

static const std::uint32_t cGenerations = 50;
static const std::uint32_t cPopulationCount = 1000;
static const float cCrossingProbability = 0.75;
static const float cMutationProbability = 0.001;

static const std::function<double(genixx::Individual& individual)> cAssessmentFunction =
    [](genixx::Individual& individual) -> double {
    auto phenotype = dynamic_cast<genixx::NumericChromosome<double>*>(individual.chromosome("x").get())->phenotype();
    return (std::exp(phenotype) * std::sin(M_PI * phenotype) + 1.0) / phenotype;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Creating new population consisting of individuals with specified chromosome crossing strategy
    genixx::Individual::mutationProbability(cMutationProbability);
    genixx::Population population(cCrossingProbability);
    for (std::uint32_t individual = 0; individual < cPopulationCount; individual++)
    {
        auto ind = genixx::Individual({{"x", genixx::NumericChromosome<double>::random(15, 1.5, 3.5)}});
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
        dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("x").get())
            ->phenotype());

    for (std::uint32_t generation = 0; generation <= cGenerations; generation++)
    {
        population = population.nextGeneration(genixx::selection::roulette);
        population.assessPopulation(cAssessmentFunction);
        std::cout << fmt::format(
            "{:<28} {:<32} {:<36} {:<40}\n",
            population.generation(),
            population.averageScore(),
            population.bestScore(),
            dynamic_cast<genixx::NumericChromosome<double>*>(population.bestIndividual().chromosome("x").get())
                ->phenotype());
    }
    return 0;
}
