#ifndef ABSTRACT_TRANSFORMATION_H
#define ABSTRACT_TRANSFORMATION_H

#include "../vector/AbstractVector.h"
#include <array>

template <typename ScalarType, int inputDimension, int outputDimension>
class AbstractTransformation {



    public :

    virtual std::array<ScalarType, outputDimension> transform(const std::array<ScalarType, inputDimension>& input);

};

#endif