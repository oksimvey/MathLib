#ifndef LINEAR_TRANSFORMATION_H
#define LINEAR_TRANSFORMATION_H

#include "AbstractTransformation.h"

template <typename ScalarType, int inputDimension, int outputDimension>
class LinearTransformation : public AbstractTransformation<ScalarType, inputDimension, outputDimension> {


    const AbstractVector<outputDimension, ScalarType> vectors[inputDimension];

    public:



};


#endif