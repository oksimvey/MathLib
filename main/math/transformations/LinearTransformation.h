#ifndef LINEARTRANSFORMATION_H
#define LINEARTRANSFORMATION_H

#include "math/transformations/Transformation.h"

#include <string>

#include "math/vectors/AbstractVector.h"

#include "math/ComplexNumber.h"

#include <vector>

template <int input_dim, int output_dim>

class LinearTransformation : public Transformation<input_dim, output_dim> {

  public:

    static LinearTransformation identity(int dimension);

    static LinearTransformation rotationMatrixByPlaneIndex(float theta,
                                                           std::pair<int, int> plane);
                                                           
    std::array<AbstractVector<output_dim>, input_dim> basis;

    template <typename... Vectors>
    LinearTransformation(const Vectors&... vectors) : basis{vectors...} {
        static_assert(sizeof...(Vectors) == input_dim, "Wrong number of basis vectors");
    }
    AbstractVector<output_dim>
    transform(const AbstractVector<input_dim>& vector) const override {
        AbstractVector<output_dim> toreturn;
        for (int i = 0; i < input_dim; i++) {
            toreturn = toreturn + (basis[i] * vector.getComponents()[i]);
        }
        return toreturn;
    }

    LinearTransformation operator*(const float& scalar) const;

    LinearTransformation operator/(const float& scalar) const;

    AbstractVector<output_dim> operator*(const AbstractVector<input_dim>& vector) const {
        return transform(vector);
    }
    
    template <int input_dim2>
    LinearTransformation<input_dim2, output_dim>
    operator*(const LinearTransformation<input_dim2, input_dim>& transformation) const {

        std::array<AbstractVector<output_dim>, input_dim2> result;

        for (int i = 0; i < input_dim2; i++) {
            result[i] = (*this) * transformation.getBasis()[i];
        }

        return LinearTransformation<input_dim2, output_dim>(result);
    }

    LinearTransformation operator/(const LinearTransformation& transformation) const;

    LinearTransformation operator+(const AbstractVector<input_dim>& vector) const;

    LinearTransformation operator+(const LinearTransformation& transformation) const;

    LinearTransformation operator+(const float& number) const;

    LinearTransformation operator-(const AbstractVector<input_dim>& vector) const;

    LinearTransformation
    operator-(const LinearTransformation<input_dim, output_dim>& transformation) const;

    LinearTransformation operator-(const ComplexNumber& number) const;

    LinearTransformation operator-(const float& number) const;

    std::vector<AbstractVector<output_dim>> kerr() const;

    std::vector<AbstractVector<output_dim>> im() const;

    std::vector<AbstractVector<output_dim>> getBasis() const;

    LinearTransformation transpose() const;

    LinearTransformation inverse() const;

    float trace() const;

    std::vector<float> eigenValues() const;

    std::vector<AbstractVector<output_dim>> eigenVectors() const;

    LinearTransformation diagonalize() const;

    int null() const;

    int rank() const;

    float det() const;

    bool isOrtonormal() const;

    std::string print() const {
        std::string result;

        for (int row = 0; row < output_dim; row++) {
            result += "[ ";

            for (int col = 0; col < input_dim; col++) {
                result += std::to_string(basis[col].getComponents()[row]);

                if (col < input_dim - 1)
                    result += " ";
            }

            result += " ]\n";
        }

        return result;
    }
};

#endif