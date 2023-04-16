#pragma once

#include <cstdint>
#include <random>

const auto pi = 3.14159265359;

template <typename Type1, typename Type2>
std::uint32_t random(Type1 begin, Type2 end)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(begin, end);
    return distr(gen);
}
