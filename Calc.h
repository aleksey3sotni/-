#pragma once
#include <vector>
#include <cstdint>
#include <boost/numeric/conversion/cast.hpp>

class Calc {
private:
    std::vector<int32_t> data;
    int32_t result;
public:
    Calc(const std::vector<int32_t>& inputData);
    int32_t get_result() const;
};
