#pragma once
#include <vector>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>

class Calc {
    int32_t results;
public:
    Calc(std::vector<int32_t> input_data);
    int32_t send_res();
};
