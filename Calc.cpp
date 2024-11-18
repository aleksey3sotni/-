#include "Calc.h"
#include <limits>
#include <stdexcept>
#include <vector>

Calc::Calc(const std::vector<int32_t>& inputData) : data(inputData), result(1) { 
    if (data.empty()) {
        result = 0;
    }
}

int32_t Calc::get_result() const {
    if (data.empty()) {
        return 0;
    }
    int32_t result = 1;
    for (int32_t val : data) {
        if (val == 0) {
            return 0; 
        }
        
        if ((result > 0 && val > std::numeric_limits<int32_t>::max() / result) ||
            (result < 0 && val < std::numeric_limits<int32_t>::min() / result)) {
            throw std::overflow_error("Integer overflow during multiplication");
        }
        result *= val;
    }
    return result;
}
