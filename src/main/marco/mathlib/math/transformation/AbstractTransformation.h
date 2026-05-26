#ifndef ABSTRACT_TRANSFORMATION_H
#define ABSTRACT_TRANSFORMATION_H

#include "../vector/AbstractVector.h"

template <typename ScalarType, int inputDimension, int outputDimension>
class AbstractTransformation {



    public :

    virtual AbstractVector<outputDimension, ScalarType> transform(const AbstractVector<inputDimension, ScalarType>& input) const = 0;

};

#endif