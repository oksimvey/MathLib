#ifndef ABSTRACTVECTOR_H
#define ABSTRACTVECTOR_H

#include <array>
#include <cmath>
#include <string>
#include <math/vectors/IVector.h>

// the vector dimension/number of components
template <int dim>

// abstract vector of dimension n
class AbstractVector : public IVector {

  public:

    std::array<float, dim> components;

    // constructors
    AbstractVector() {
        components.fill(0.0f);
    }

    template <typename T>
    static float toFloat(T value) {
        return static_cast<float>(value);
    }

    template <typename... Args>
    explicit AbstractVector(Args... args)
        : components{toFloat(args)...}
    {
        static_assert(sizeof...(Args) == dim, "Wrong dimension");
    }


    // getters
    static constexpr int getDimension() {
        return dim;
    }

    const std::array<float, dim>& getComponents() const {
        return components;
    }

    // vector sum
    AbstractVector operator+(const AbstractVector& vec) const {
        AbstractVector result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] + vec.components[i];
        }

        return result;
    }

    AbstractVector operator +=(const AbstractVector& vec) const {
        return *this + vec;
    }

    // vector subtraction
    AbstractVector<dim> operator-(const AbstractVector<dim>& vec) const {
        AbstractVector<dim> result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] - vec.components[i];
        }

        return result;
    }

    AbstractVector operator -=(const AbstractVector<dim>& vec) const {
        return *this - vec;
    }


    // scalar multiplication
    AbstractVector<dim> operator*(float scalar) const {
        AbstractVector<dim> result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] * scalar;
        }

        return result;
    }

    AbstractVector operator*=(float scalar) const {
        return *this * scalar;
    }

    // scalar division
    AbstractVector<dim> operator/(float scalar) const {
        AbstractVector<dim> result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] / scalar;
        }

        return result;
    }

    AbstractVector operator/=(float scalar) const {
        return *this / scalar;
    }

    // returns the dot product v1u1 + v2u2 + v3u3...
    float operator*(const AbstractVector<dim>& vec) const {
        float sum = 0;

        for (int i = 0; i < dim; i++) {
            sum += components[i] * vec.components[i];
        }

        return sum;
    }

    // return the vector magnitude/length ||v||
    [[nodiscard]] float magnitude() const {
        return std::sqrt(*this * *this);
    }

    // normalize the vector so ||v|| = 1
    AbstractVector normalize() const {
        float mag = magnitude();

        AbstractVector result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] / mag;
        }

        return result;
    }

    // returns the distance between two vectors
    float distanceTo(const AbstractVector<dim>& vec) const {
        return (*this - vec).magnitude();
    }

    // returns the angle between the two vectors (from cos(θ) = (v*u)/||v||||u||)
    float getAngleBetween(const AbstractVector<dim>& vec) const {
        return arccos(((*this) * vec) / (magnitude() * vec.magnitude()));
    }

    // true if the vector is perpendicular to each other(cos(pi/2) = 0, v * u = 0)
    bool isPerpendicular(const AbstractVector& vec) const {
        const float& d = *this * vec;
        return d == 0;
    }


    // prints the vector as an array
    [[nodiscard]] std::string print() const {
        std::string out = "(";

        for (int i = 0; i < dim; i++) {
            out += std::to_string(components[i]);
            if (i + 1 < dim)
                out += ", ";
        }

        out += ")";
        return out;
    }
};

#endif