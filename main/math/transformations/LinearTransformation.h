#ifndef LINEARTRANSFORMATION_H
#define LINEARTRANSFORMATION_H

#include "math/transformations/Transformation.h"

#include <cmath>
#include <string>
#include "math/vectors/AbstractVector.h"
#include "math/ComplexNumber.h"
#include <vector>
#include <cassert>

// intput dim is the number of columns/vectors
// output dim is the number of lines/dim of the basis vectors
template <int input_dim, int output_dim>

class LinearTransformation : public Transformation<input_dim, output_dim> {

  public:

    // the basis vectors/colum vectors of the linear transformation
    std::array<AbstractVector<output_dim>, input_dim> basis;

    // constructors
    template <typename... Vectors>
    explicit LinearTransformation(const Vectors&... vectors) : basis{vectors...} {
        static_assert(sizeof...(Vectors) == input_dim, "Wrong number of basis vectors");
    }

    LinearTransformation() {
        for (int i = 0; i < output_dim; i++)
            basis[i] = AbstractVector<input_dim>();
    }

    // getters
    std::vector<AbstractVector<output_dim>> getBasis() const {
        return basis;
    }

    static int lines() {
        return output_dim;
    }

    static int columns() {
        return input_dim;
    }

    // basic matrix arithmetic operations

    LinearTransformation operator*(const float& scalar) const {
        LinearTransformation result;
        result.basis = basis;
        for (int i = 0; i < input_dim; i++) {
            result.basis[i] = result.basis[i] * scalar;
        }
        return result;
    }

    LinearTransformation operator/(const float& scalar) const {
        LinearTransformation result;
        result.basis = basis;
        for (int i = 0; i < input_dim; i++) {
            result.basis[i] = result.basis[i] / scalar;
        }
        return result;
    }

    LinearTransformation operator+(const LinearTransformation& transformation) const;

    LinearTransformation operator+(const float& number) const;

    LinearTransformation operator-(const LinearTransformation& transformation) const;

    LinearTransformation operator-(const float& number) const;


    // matrix operations

    AbstractVector<output_dim>
    transform(const AbstractVector<input_dim>& vector) const override {
        assert(vector.getDimension() == input_dim);
        AbstractVector<output_dim> toreturn;
        for (int i = 0; i < input_dim; i++) {
            toreturn = toreturn + basis[i] * vector.getComponents()[i];
        }
        return toreturn;
    }


    AbstractVector<output_dim> operator*(const AbstractVector<input_dim>& vector) const {
        return transform(vector);
    }

    LinearTransformation operator*(const LinearTransformation& transformation) const {

        LinearTransformation result;

        result.inDim = transformation.getInputDimension();
        result.outDim = this-> getOutputDimension();

        result.basis.resize(result.getInputDimension());

        for (int i = 0; i < result.getInputDimension(); i++) {
            result.basis[i] = *this * transformation.basis[i];
        }

        return result;
    }

    LinearTransformation operator^(const int& expoent) const;

    LinearTransformation operator/(const LinearTransformation& transformation) {
        return *this * transformation.inverse();
    }

    LinearTransformation exp() const;

    bool isOrthonormal() const;

    float trace() const;

    std::vector<AbstractVector<output_dim>> im() const;

    std::vector<AbstractVector<output_dim>> kerr() const;

    int null() const;

    int rank() const;

    LinearTransformation transpose() const;

    float det() const;

    LinearTransformation adjoint() const;

    LinearTransformation inverse() const;

    std::vector<float> eigenValues() const;

    std::vector<AbstractVector<output_dim>> eigenVectors() const;

    LinearTransformation diagonalize() const;


    std::string print() const {
        std::string result;

        for (int row = 0; row < output_dim; row++) {
            result += "[ ";

            for (int col = 0; col < input_dim; col++) {
                result += std::to_string(basis[col].getComponents()[row]);

                if (col < input_dim - 1)
                    result += ", ";
            }

            result += " ]\n";
        }

        return result;
    }
};


template<int dimension>
LinearTransformation<dimension, dimension> identity() {

    LinearTransformation<dimension, dimension> result = LinearTransformation<dimension, dimension>();

    for (int i = 0; i < dimension; i++) {
        result.basis[i].components[i] = 1;
    }

    return result;
}

template<int dimension>
LinearTransformation<dimension, dimension> antissymetric(const AbstractVector<dimension>& vector){}

template<int dimension>
LinearTransformation<dimension, dimension> rotationByPlaneIndex(const int& i, const int& j, const float& theta) {

    assert(i >= 0 && i < dimension);
    assert(j >= 0 && j < dimension);
    assert(i != j);

    LinearTransformation<dimension, dimension> result = identity<dimension>();
    const float cosTheta = std::cos(theta);
    const float sinTheta = std::sin(theta);
    result.basis[i].components[i] = cosTheta;
    result.basis[j].components[j] = cosTheta;
    result.basis[i].components[j] = sinTheta;
    result.basis[j].components[i] = -sinTheta;
    return result;
}

LinearTransformation<2, 2> rotationIn2D(const float& theta) {
    return rotationByPlaneIndex<2>(0, 1, theta);
}

LinearTransformation<3, 3> rotationInXAxis(const float& theta) {
    return rotationByPlaneIndex<3>(1,2, theta);
}

LinearTransformation<3, 3> rotationInYAxis(const float& theta) {
    return rotationByPlaneIndex<3>(0,2, theta);
}

LinearTransformation<3, 3> rotationInZAxis(const float& theta) {
    return rotationByPlaneIndex<3>(0,1, theta);
}

#endif