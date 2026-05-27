#ifndef MATHLIB_SCALAR_H
#define MATHLIB_SCALAR_H


#include "ComplexNumber.h"
#include <type_traits>
class Scalar {

    public:

    
template <typename T>
static inline constexpr bool isScalar =
    std::is_same_v<T, int> ||
    std::is_same_v<T, float> ||
    std::is_same_v<T, double> ||
    std::is_same_v<T, ComplexNumber> ||
    std::is_same_v<T, RealNumber>;

};

#endif // MATHLIB_SCALAR_H