#include "genixx/utils/random.h"

#include <catch2/catch_all.hpp>

#include <cstdint>

using namespace genixx;

const auto cIterations = 2000;

TEST_CASE("Random always in range")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        REQUIRE(random(0, 1) <= 1);
    }
}

TEST_CASE("Random always in range for floating point values")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(0.5, 2.5);
        REQUIRE(num >= 0.5);
        REQUIRE(num <= 2.5);
    }
}

TEST_CASE("Random always in range for negative floating point values")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(-2.5, -0.5);
        REQUIRE(num <= -0.5);
        REQUIRE(num >= -2.5);
    }
}

TEST_CASE("Random always in range for floating point and integral numbers")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(2.5, 10);
        REQUIRE(num <= 10);
        REQUIRE(num >= 2.5);
    }
}
