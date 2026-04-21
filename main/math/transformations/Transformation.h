#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "math/vectors/AbstractVector.h"


// input dim is the dimension of the vectors to be transformed
// output dim is the dimension of the transformed vectors
template <int input_dim, int output_dim>

class Transformation {

  public:

    virtual ~Transformation() = default;

    virtual AbstractVector<output_dim>
    
    transform(const AbstractVector<input_dim>& vec) const = 0;

    static constexpr int getInputDimension() {
        return input_dim;
    }

    static constexpr int getOutputDimension() {
        return output_dim;
    }
};

#endif