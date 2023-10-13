#include "genixx/chromosome/NumericChromosome.h"
#include "genixx/population/Individual.h"
#include "genixx/population/selection/method.h"

#include <catch2/catch_all.hpp>

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <tuple>

std::tuple<genixx::selection::Individuals, genixx::selection::Scores> dataset(std::uint32_t size)
{
    genixx::selection::Individuals individuals;
    genixx::selection::Scores scores(size);
    for (std::uint32_t i = 0; i < size; i++)
    {
        // Different range to make sure every individual is going to be recognizable by it's phenotype.
        individuals.emplace_back(
            genixx::Individual({{"x", genixx::NumericChromosome<double>::random(11, i, i + 0.5)}}));
        scores[i] = static_cast<double>(i);
    }
    return {individuals, scores};
}

inline std::uint32_t sumOfSubsequent(std::uint32_t num)
{
    return (num == 1 || num == 0) ? num : sumOfSubsequent(num - 1) + num;
}

TEST_CASE("Sanity check")
{
    REQUIRE(sumOfSubsequent(0) == 0);
    REQUIRE(sumOfSubsequent(1) == 1);
    REQUIRE(sumOfSubsequent(2) == 3);
    REQUIRE(sumOfSubsequent(3) == 6);
    REQUIRE(sumOfSubsequent(4) == 10);
    REQUIRE(sumOfSubsequent(5) == 15);
    REQUIRE(sumOfSubsequent(6) == 21);
    REQUIRE(sumOfSubsequent(7) == 28);
    REQUIRE(sumOfSubsequent(8) == 36);
    REQUIRE(sumOfSubsequent(9) == 45);
    REQUIRE(sumOfSubsequent(10) == 55);
}

// Only ranking method can be tested.
// Roullette is more of a random act, which only increases odds of high scoring individuals to be selected, however it's
// not guaranteed.
TEST_CASE("Ranking method")
{
    std::uint32_t size = 1000;

    [[maybe_unused]] auto expectedOccurrences = [size](std::uint32_t arg) -> std::uint32_t {
        return (((static_cast<double>(size) / static_cast<double>(sumOfSubsequent(size - 1))) * arg) * 2);
    };
    auto [individuals, scores] = dataset(size);
    std::map<std::uint32_t, std::uint32_t> individualOccurrencesAfterSelection;

    auto newPopulation = genixx::selection::ranking(individuals, scores);

    for (auto& individual : newPopulation)
    {
        individualOccurrencesAfterSelection[std::floor(
            dynamic_cast<genixx::NumericChromosome<double>*>(individual.chromosome("x").get())->phenotype())]++;
    }

    REQUIRE(newPopulation.size() == size);

    // It is expected that at least 25% of lowest scoring individuals will be discarded.
    for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(size / 4); i++)
    {
        REQUIRE(individualOccurrencesAfterSelection.find(i) == individualOccurrencesAfterSelection.end());
    }

    // It is expected that at least 25% of highest scoring individuals will have their occurrences in new population
    // certain amount.
    for (std::uint32_t i = 1; i < std::floor(size / 4); i++)
    {
        REQUIRE(individualOccurrencesAfterSelection[size - i] == expectedOccurrences(size - i));
    }
}
