#include "Calc.h"

Calc::Calc(std::vector<int32_t> input_data) {
    try {
        int32_t temp_res = 1; 
        for (auto elem : input_data) {
            temp_res = boost::numeric_cast<int32_t>(temp_res * elem);
        }
        results = temp_res;
    } catch (boost::numeric::negative_overflow& e) {
        results = std::numeric_limits<int32_t>::lowest();
    } catch (boost::numeric::positive_overflow& e) {
        results = std::numeric_limits<int32_t>::max();
    }
}

int32_t Calculator::send_res() {
    return results;
}
        


