//
// Created by hapoe on 4/21/2026.
//

#ifndef MATHLIB_MAIN_VECTOR2D_H
#define MATHLIB_MAIN_VECTOR2D_H

#include <cmath>
#include "math/vectors/IVector.h"

class Vector2D : public IVector {

public:

    // x and y components of the vector
    const float& x, y;

    // constructors
    Vector2D(const float& x_, const float& y_) : x(x_), y(y_) {}

    Vector2D() : Vector2D(0, 0) {}

    // getters

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    // operations

    Vector2D operator+(const Vector2D& o) const {
        return Vector2D(x + o.x, y + o.y);
    }

    Vector2D operator+=(const Vector2D& o) const {
        return *this + o;
    }

    Vector2D operator-(const Vector2D& o) const {
        return Vector2D(x - o.x, y - o.y);
    }

    Vector2D operator-=(const Vector2D& o) const {
        return *this - o;
    }

    Vector2D operator*(const float& scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D operator*=(const float& scalar) const {
        return *this * scalar;
    }

    Vector2D operator/(const float& scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D operator/=(const float& scalar) const {
        return *this / scalar;
    }

    // vector operations

    float dotProduct(const Vector2D& vec) const {
        return x * vec.x + y * vec.y;
    }

    float length() const {
        return std::sqrt(dotProduct(*this));
    }

    Vector2D normalize() const {
        return *this / length();
    }

    float distanceTo(const Vector2D& vec) const {
        return (*this - vec).length();
    }

    float getAngleBetween(const Vector2D& vec) const {
        return std::acos(dotProduct(vec) / (length() * vec.length()));
    }

    float isPerpendicular(const Vector2D& vec) const {
        return dotProduct(vec) == 0;
    }

    Vector2D normal() const {
        return Vector2D(-y, x);
    }

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

};

#endif //MATHLIB_MAIN_VECTOR2D_H

