#ifndef ABSTRACTVECTOR_H
#define ABSTRACTVECTOR_H

#include <array>
#include <cmath>
#include <string>

#include "math/ComplexNumber.h"

template <int dim>

class AbstractVector {

  public:
    std::array<float, dim> components;

    // =========================
    // constructors
    // =========================

    AbstractVector() {
        components.fill(0.0f);
    }

    template <typename T> static float toComplex(T value) {
        return static_cast<float>(value);
    }

    static ComplexNumber toComplex(const ComplexNumber& value) {
        return value;
    }

    template <typename... Args>
    AbstractVector(Args... args) : components{toComplex(args)...} {
        static_assert(sizeof...(Args) == dim, "Wrong dimension");
    }
    // =========================
    // getters
    // =========================

    constexpr int getDimension() const {
        return dim;
    }

    const std::array<float, dim>& getComponents() const {
        return components;
    }

    // =========================
    // math core
    // =========================

     float magnitude() const {
        return std::sqrt((*this) * (*this));
    }

    AbstractVector<dim> normalize() const {
        float mag = magnitude();

        AbstractVector result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] / mag;
        }

        return result;
    }

    // =========================
    // operators
    // =========================

    AbstractVector<dim> operator+(const AbstractVector<dim>& vec) const {
        AbstractVector<dim> result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] + vec.components[i];
        }

        return result;
    }

    AbstractVector<dim> operator-(const AbstractVector<dim>& vec) const {
        AbstractVector<dim> result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] - vec.components[i];
        }

        return result;
    }

    

    AbstractVector<dim> operator*(float scalar) const {
          AbstractVector<dim> result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] * scalar;
        }

        return result;
    }

    

    AbstractVector<dim> operator/(float scalar) const {
        AbstractVector<dim> result;

        for (int i = 0; i < dim; i++) {
            result.components[i] = components[i] / scalar;
        }

        return result;
    }

    float operator*(const AbstractVector<dim>& vec) const {
        float sum = 0;

        for (int i = 0; i < dim; i++) {
            sum += components[i] * vec.components[i];
        }

        return sum;
    }

    // =========================
    // geometry
    // =========================

    float distanceTo(const AbstractVector<dim>& vec) const {
        return (*this - vec).magnitude();
    }

    AbstractVector<dim> crossProduct(const std::array<AbstractVector<dim>, dim - 1>) {
    }

    float getAngleBetween(const AbstractVector<dim>& vec) const {
        return arccos((((*this) * vec) / (magnitude() * vec.magnitude())));
    }

    bool isPerpendicular(const AbstractVector<dim>& vec) const {
        float d = (*this) * vec;
        return d == 0;
    }

    // =========================
    // utils
    // =========================

    std::string print() const {
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