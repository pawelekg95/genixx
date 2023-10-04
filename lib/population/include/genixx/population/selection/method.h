#pragma once

#include "genixx/utils/random.h"

#include <algorithm>
#include <functional>
#include <map>

namespace genixx::selection {

using Scores = std::vector<double>;
using SelectionMethod = std::function<std::vector<Individual>(std::vector<Individual>, Scores)>;

static const SelectionMethod roulette = [](std::vector<Individual> oldPopulation,
                                           Scores scores) -> std::vector<Individual> {
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

    for (std::uint32_t i = 0; i < populationSize; i++)
    {
        std::uint32_t j{};
        while (randoms[i] > rouletteWheel[++j] && j < rouletteWheel.size() - 1)
            ;
        if (j >= oldPopulation.size())
        {
            continue;
        }
        newGeneration.emplace_back(oldPopulation[j].copy());
    }
    return newGeneration;
};

static const SelectionMethod ranking = [](std::vector<Individual> oldPopulation,
                                          Scores scores) -> std::vector<Individual> {
    auto populationSize = oldPopulation.size() * 2;
    std::vector<Individual> newGeneration;
    double scoreSum = std::accumulate(scores.begin(), scores.end(), 0.0);
    double copiesPerScore = static_cast<double>(populationSize) / scoreSum;
    int maxSpins = oldPopulation.size();

    while (newGeneration.size() < oldPopulation.size() && maxSpins > 0)
    {
        std::uint32_t i = std::max_element(scores.begin(), scores.end()) - scores.begin();
        auto copiesToPopulate = std::floor(scores[i] * copiesPerScore);
        for (std::uint32_t j = 0; j < copiesToPopulate; j++)
        {
            if (newGeneration.size() >= oldPopulation.size())
            {
                break;
            }
            newGeneration.emplace_back(oldPopulation[i].copy());
        }
        scores[i] = 0;
        maxSpins--;
    }

    return newGeneration;
};

} // namespace genixx::selection
