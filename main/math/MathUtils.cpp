#include "MathUtils.h"
#include <cmath>

namespace MathUtils {

    bool isNearZero(float x) {
        return std::abs(x) < EPS;
    }

    bool areEqual(float a, float b) {
        return std::abs(a - b) < EPS;
    }
    
}