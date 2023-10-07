#pragma once

#include <cmath>
#include <cstdint>
#include <random>
#include <type_traits>

namespace {

template <typename Type1, typename Type2, typename>
struct SignTrait
{
    using type = Type1;
};

template <typename Type1, typename Type2>
struct SignTrait<Type1, Type2, std::false_type>
{
    using type = Type2;
};

template <typename Type1, typename Type2, typename>
struct FloatingPointTrait
{
    using distr = std::uniform_real_distribution<>;
};

template <typename Type1, typename Type2>
struct FloatingPointTrait<Type1, Type2, std::false_type>
{
    using distr = std::uniform_int_distribution<>;
};

template <typename Type1, typename Type2>
struct NumberTrait
    : SignTrait<Type1, Type2, std::is_signed<Type1>()>
    , FloatingPointTrait<Type1, Type2, std::is_floating_point<Type1>()>
{};

} // namespace

namespace genixx {

template <typename Type1, typename Type2>
typename NumberTrait<Type1, Type2>::type random(Type1 begin, Type2 end)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    typename NumberTrait<Type1, Type2>::distr distr(begin, end);
    return distr(gen);
}

} // namespace genixx
