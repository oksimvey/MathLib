//
// Created by hapoe on 4/21/2026.
//

#ifndef MATHLIB_MAIN_VECTOR3D_H
#define MATHLIB_MAIN_VECTOR3D_H
#include <bits/valarray_after.h>
#include <cmath>
#include "math/vectors/IVector.h"

class Vector3D : public IVector {

public:

    // x, y and z components of the vector
    const float& x, y, z;

    // constructors
    Vector3D(const float& x_, const float& y_, const float& z_) : x(x_), y(y_), z(z_) {}

    Vector3D() : Vector3D(0, 0, 0) {}

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

    // basic vector operations

    Vector3D operator+(const Vector3D& o) const {
        return Vector3D(x + o.x, y + o.y, z + o.z);
    }

    Vector3D operator+=(const Vector3D& o) const {
        return *this + o;
    }

    Vector3D operator-() const {
        return Vector3D(-x, -y, -z);
    }

    Vector3D operator-(const Vector3D& o) const {
        return Vector3D(x - o.x, y - o.y, z - o.z);
    }

    Vector3D operator-=(const Vector3D& o) const {
        return *this - o;
    }

    Vector3D operator*(const float& scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D operator*=(const float& scalar) const {
        return *this * scalar;
    }

    Vector3D operator/(const float& scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    Vector3D operator/=(const float& scalar) const {
        return *this / scalar;
    }

    // cross product (returns a vector perpendicular to both vectors, and magnitude equal to the paralelogram they form
    Vector3D operator^(const Vector3D& o) const {
        return Vector3D(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }

    Vector3D operator^=(const Vector3D& o) const {
        return *this ^ o;
    }


    // vector operations
    float dotProduct(const Vector3D& vec) const {
        return x * vec.x + y * vec.y + z * vec.z;
    }
    float length() const {
        return std::sqrt(dotProduct(*this));
    }

    Vector3D normalize() const {
        return *this / length();
    }

    float distanceTo(const Vector3D& vec) const {
        return (*this - vec).length();
    }

    float getAngleBetween(const Vector3D& vec) const {
        return std::acos(dotProduct(vec) / (length() * vec.length()));
    }

    bool isPerpendicular(const Vector3D& vec) const {
        return dotProduct(vec) == 0;
    }

};

#endif //MATHLIB_MAIN_VECTOR3D_H
