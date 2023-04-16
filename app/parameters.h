#pragma once

#include <cstdint>
#include <filesystem>

namespace parameters {

struct Parameters
{
    std::uint32_t generations{};
    double searchingAreaBegin{};
    double searchingAreaEnd{};
    std::uint32_t population{};
    double crossingProbability{};
    double mutationProbability{};
};

Parameters load(const std::filesystem::path& path);

static constexpr std::uint32_t cGenes{11};

} // namespace parameters
