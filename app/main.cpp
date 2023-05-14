#include "Population.h"
#include "dump.h"
#include "parameters.h"

#include <fmt/core.h>

#include <iostream>

// Team: G1

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    auto currentPath = std::filesystem::canonical("/proc/self/exe").parent_path();
    auto parameters = parameters::load(currentPath / "parameters.json");
    Population population(parameters);
    population.calculatePhenotypes();
    population.checkCorrectness();

    std::vector<std::uint32_t> generationsVector(parameters.generations);
    std::vector<double> averageCorrectnessVector(parameters.generations);
    std::vector<double> maxCorrectnessVector(parameters.generations);
    std::cout << fmt::format("{:<28} {:<32} {:<36}\n", "Generation", "Average correctness", "Maximum correctness");
    for (std::uint32_t generation = 0; generation < parameters.generations; generation++)
    {
        population.roulette();
        population.crossing();
        population.mutate();
        population.calculatePhenotypes();
        population.checkCorrectness();
        auto averageCorrectness = population.averageCorrectness();
        auto maxCorrectness = population.maxCorrectness();
        std::cout << fmt::format("{:<28} {:<32} {:<36}\n", generation, averageCorrectness, maxCorrectness);

        generationsVector[generation] = generation;
        averageCorrectnessVector[generation] = averageCorrectness;
        maxCorrectnessVector[generation] = maxCorrectness;
    }

    std::cout << fmt::format("Best phenotype: {}\n", population.maxCorrectnessPhenotype());
    std::getchar();

    std::cout << "Dumping data to file data.json" << std::endl;

    dump({generationsVector, averageCorrectnessVector, maxCorrectnessVector});
    return 0;
}
