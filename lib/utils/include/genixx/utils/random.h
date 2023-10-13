#pragma once

#include "genixx/error/exceptions.h"

#include <fmt/core.h>

#include <cmath>
#include <cstdint>
#include <random>
#include <type_traits>

namespace {

template <typename Type1, typename Type2>
struct NumberTrait
{
    using type = typename std::conditional_t<(std::is_floating_point_v<Type1> || std::is_floating_point_v<Type2>),
                                             std::conditional_t<std::is_floating_point_v<Type1>, Type1, Type2>,
                                             std::conditional_t<std::is_signed_v<Type1>, Type1, Type2>>;

    using distr = typename std::conditional_t<std::is_floating_point_v<type>,
                                              std::uniform_real_distribution<>,
                                              std::uniform_int_distribution<>>;
};

} // namespace

namespace genixx {

template <typename Type1,
          typename Type2,
          typename = std::enable_if_t<std::is_arithmetic_v<Type1>>,
          typename = std::enable_if_t<std::is_arithmetic_v<Type2>>>
typename NumberTrait<Type1, Type2>::type random(Type1 begin, Type2 end)
{
    if constexpr (std::is_signed_v<Type1> == std::is_signed_v<Type2>)
    {
        if (begin > end)
        {
            throw InvalidArgumentException(fmt::format("Invalid range!"));
        }
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    typename NumberTrait<Type1, Type2>::distr distr(begin, end);
    return distr(gen);
}

} // namespace genixx
