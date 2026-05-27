#ifndef LINEAR_TRANSFORMATION_H
#define LINEAR_TRANSFORMATION_H

#include "AbstractTransformation.h"
#include "../number/Scalar.h"

template <typename ScalarType, int inputDimension, int outputDimension>
class LinearTransformation : public AbstractTransformation<ScalarType, inputDimension, outputDimension> {


    const AbstractVector<outputDimension, ScalarType> vectors[inputDimension];

    public:

      static_assert(inputDimension > 0, "Input Dimension must be greater than 0");

    static_assert(outputDimension > 0, "Output Dimension must be greater than 0");

    static_assert(Scalar::isScalar<ScalarType>, "Invalid scalar type");



};


#endif