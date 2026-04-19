#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "math/vectors/AbstractVector.h"

template <int input_dim, int output_dim>

class Transformation {

  public:
    virtual ~Transformation() = default;

    virtual AbstractVector<output_dim>
    
    transform(const AbstractVector<input_dim>& vec) const = 0;

    constexpr int getInputDimension() const {
        return input_dim;
    }

    constexpr int getOutputDimension() const {
        return output_dim;
    }
};

#endif