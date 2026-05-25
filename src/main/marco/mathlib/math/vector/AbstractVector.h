#ifndef ABSTRACT_VECTOR_H
#define ABSTRACT_VECTOR_H
#include "../number/Scalar.h"

template <int Dimension, typename ScalarType>

class AbstractVector {

       static_assert(Dimension > 0,
                  "Dimension must be greater than 0");


};

#endif // ABSTRACT_VECTOR_H