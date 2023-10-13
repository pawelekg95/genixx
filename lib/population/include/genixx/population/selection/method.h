#pragma once

#include "genixx/population/Individual.h"
#include "genixx/utils/random.h"

#include <algorithm>
#include <functional>
#include <map>

namespace genixx::selection {

using Scores = std::vector<double>;
using Individuals = std::vector<Individual>;
using SelectionMethod = std::function<Individuals(Individuals, Scores)>;

static const SelectionMethod roulette = [](Individuals oldPopulation, Scores scores) -> Individuals {
    auto populationSize = oldPopulation.size();
    Individuals newGeneration;
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

static const SelectionMethod ranking = [](Individuals oldPopulation, Scores scores) -> Individuals {
    auto populationSize = 2 * oldPopulation.size();
    Individuals newGeneration;
    double scoreSum = std::accumulate(scores.begin(), scores.end(), 0.0);
    double copiesPerScore = static_cast<double>(populationSize) / scoreSum;

    for (std::uint32_t i = 0; i < oldPopulation.size(); i++)
    {
        if (newGeneration.size() >= oldPopulation.size())
        {
            break;
        }
        auto maxElemIt = std::max_element(scores.begin(), scores.end());
        if (maxElemIt == scores.end())
        {
            break;
        }
        auto copiesToPopulate = std::floor(*maxElemIt * copiesPerScore);
        for (std::uint32_t j = 0; j < copiesToPopulate; j++)
        {
            if (newGeneration.size() >= oldPopulation.size())
            {
                break;
            }
            auto individualIt = maxElemIt - scores.begin();
            newGeneration.emplace_back(oldPopulation[individualIt].copy());
        }
        *maxElemIt = 0;
    }

    return newGeneration;
};

} // namespace genixx::selection
