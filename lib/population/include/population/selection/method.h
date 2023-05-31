#pragma once

#include "utils/random.h"

#include <algorithm>
#include <functional>
#include <map>

namespace genixx::selection {

using SelectionMethod = std::function<std::vector<Individual>(std::vector<Individual>, std::vector<double>)>;

static const SelectionMethod roulette = [](std::vector<Individual> oldPopulation, std::vector<double> scores) -> std::vector<Individual> {
    auto populationSize = oldPopulation.size();
    std::vector<Individual> newGeneration;
    double scoreSum = std::accumulate(scores.begin(), scores.end(), 0.0);

    std::vector<std::uint32_t> randoms(populationSize);

    for (auto& num : randoms)
    {
        num = random(0, std::abs(scoreSum));
    }

    std::vector<double> rouletteWheel(populationSize);
    double position{};
    for (std::uint32_t i = 0; i < populationSize; i++)
    {
        position += scores[i];
        rouletteWheel[i] = position;
    }

    for (std::uint32_t i = 0; i < populationSize / 2; i++)
    {
        std::uint32_t j{};
        while (randoms[i] > rouletteWheel[++j] && j < rouletteWheel.size());
        if (j >= oldPopulation.size())
        {
            continue;
        }
        newGeneration.emplace_back(oldPopulation[j].copy());
    }
    return newGeneration;
};

} // namespace genixx::selection
