#include "genixx/utils/random.h"

#include <catch2/catch_all.hpp>

#include <cstdint>
#include <cstring>
#include <type_traits>

using namespace genixx;

const auto cIterations = 2000;

TEST_CASE("Random always in range")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto rand = random(0, 1);
        REQUIRE(std::is_integral<decltype(rand)>());
        REQUIRE(random(0, 1) <= 1);
    }
}

TEST_CASE("Random always in range for floating point values")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(0.5, 2.5);
        REQUIRE(std::is_floating_point<decltype(num)>());
        REQUIRE(num >= 0.5);
        REQUIRE(num <= 2.5);
    }
}

TEST_CASE("Random always in range for negative floating point values")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(-2.5, -0.5);
        REQUIRE(std::is_floating_point<decltype(num)>());
        REQUIRE(num <= -0.5);
        REQUIRE(num >= -2.5);
    }
}

TEST_CASE("Random always in range for floating point and integral numbers")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(2.5, 10);
        REQUIRE(std::is_floating_point<decltype(num)>());
        REQUIRE(num <= 10);
        REQUIRE(num >= 2.5);
    }

    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(2, 10.5);
        REQUIRE(std::is_floating_point<decltype(num)>());
        REQUIRE(num <= 10.5);
        REQUIRE(num >= 2);
    }
}

TEST_CASE("Random always have valid sign")
{
    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(std::int32_t(1), std::uint32_t(10));
        REQUIRE(std::is_signed_v<decltype(num)>);
        REQUIRE(num <= 10);
        REQUIRE(num >= 1);
    }

    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(std::uint32_t(1), std::int32_t(10));
        REQUIRE(std::is_signed_v<decltype(num)>);
        REQUIRE(num <= 10);
        REQUIRE(num >= 1);
    }

    for (std::uint32_t i = 0; i < cIterations; i++)
    {
        auto num = random(std::uint32_t(1), std::uint32_t(10));
        REQUIRE(!std::is_signed_v<decltype(num)>);
        REQUIRE(num <= 10);
        REQUIRE(num >= 1);
    }
}

TEST_CASE("Expected exceptions")
{
    try
    {
        random(50, 3);
        REQUIRE(false);
    }
    catch (std::exception& e)
    {
        REQUIRE(std::strcmp(e.what(), genixx::InvalidArgumentException("Invalid range!").what()) == 0);
    }
}
