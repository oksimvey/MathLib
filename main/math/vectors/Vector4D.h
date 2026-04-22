//
// Created by hapoe on 4/21/2026.
//

#ifndef MATHLIB_MAIN_VECTOR4D_H
#define MATHLIB_MAIN_VECTOR4D_H

#include "math/vectors/IVector.h"


class Vector4D : public IVector {

public:

    // x, y and z components of the vector
    const float& x, y, z, w;

    // constructors
    Vector4D(const float& x_, const float& y_, const float& z_, const float& w_) : x(x_), y(y_), z(z_), w(w_) {}

    Vector4D() : Vector4D(0, 0, 0, 0) {}

    // getters

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getZ() const {
        return z;
    }

    float getW() const {
        return w;
    }

    // basic vector operations

    Vector4D operator+(const Vector3D& o) const {
        return Vector4D(x + o.x, y + o.y, z + o.z, w);
    }

    Vector4D operator+=(const Vector4D& o) const {
        return *this + o;
    }

    Vector4D operator-() const {
        return Vector4D(-x, -y, -z);
    }

    Vector4D operator-(const Vector4D& o) const {
        return Vector4D(x - o.x, y - o.y, z - o.z);
    }

    Vector4D operator-=(const Vector4D& o) const {
        return *this - o;
    }

    Vector4D operator*(const float& scalar) const {
        return Vector4D(x * scalar, y * scalar, z * scalar);
    }

    Vector4D operator*=(const float& scalar) const {
        return *this * scalar;
    }

    Vector4D operator/(const float& scalar) const {
        return Vector4D(x / scalar, y / scalar, z / scalar);
    }

    Vector4D operator/=(const float& scalar) const {
        return *this / scalar;
    }

    // cross product (returns a vector perpendicular to both vectors, and magnitude equal to the paralelogram they form
    Vector4D operator^(const Vector4D& o) const {
        return Vector4D(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }

    Vector4D operator^=(const Vector4D& o) const {
        return *this ^ o;
    }


    // vector operations
    float dotProduct(const Vector4D& vec) const {
        return x * vec.x + y * vec.y + z * vec.z;
    }
    float length() const {
        return std::sqrt(dotProduct(*this));
    }

    Vector4D normalize() const {
        return *this / length();
    }

    float distanceTo(const Vector4D& vec) const {
        return (*this - vec).length();
    }

    float getAngleBetween(const Vector4D& vec) const {
        return std::acos(dotProduct(vec) / (length() * vec.length()));
    }

    bool isPerpendicular(const Vector4D& vec) const {
        return dotProduct(vec) == 0;
    }

};

#endif //MATHLIB_MAIN_VECTOR4D_H
