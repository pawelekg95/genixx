#pragma once

#include <cstdint>
#include <vector>

struct Data
{
    std::vector<std::uint32_t> generations;
    std::vector<double> averageCorrectness;
    std::vector<double> maxCorrectness;
};

void dump(const Data& data);
