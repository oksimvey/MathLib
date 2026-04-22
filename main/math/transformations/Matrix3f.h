//
// Created by hapoe on 4/21/2026.
//

#ifndef MATHLIB_MAIN_MATRIX3F_H
#define MATHLIB_MAIN_MATRIX3F_H
#include "ITransformation.h"
#include "LinearTransformation.h"
#include "math/vectors/Vector2D.h"
#include "math/vectors/Vector3D.h"
#include <cmath>

class Matrix3f : ITransformation {

public:

    // the matrix components
    /* m11, m12, m13
     * m21, m22, m23
     * m31, m32, m33
     */
    const float& components[];

    // constructors
    Matrix3f(const float& a11_, const float& a12_, const float& a13_, const float& a21_, const float& a22_, const float& a23_, const float& a31_, const float& a32_, const float& a33_)
    : components(a11_, a12_, a13_, a21_, a22_, a23_, a31_, a32_, a33_) {}

    Matrix3f() : Matrix3f(1, 0, 0, 0, 1, 0, 0, 0, 1) {}

    Matrix3f(const float& a11, const float& a21, const float& a12, const float& a22, const float& x, const float& y)
        : Matrix3f(a11,a12,x, a21, a22, y, 0, 0, 1) {
    }

    explicit Matrix3f(const Vector2D& position)
    : Matrix3f(1, 0, position.x, 0, 1, position.y, 0, 0, 1) {}

    Matrix3f(const Vector2D& v, const Vector2D& u, const Vector2D pos)
        : Matrix3f(v.x, v.y, u.x, u.y, pos.x, pos.y){}

    Matrix3f move(const Vector2D& v) const {
        return Matrix3f(a11, a21, a12, a22, a13 + v.x, a23 + v.y);
    }

    std::array<float, 2> getPos() const {
        return {components[2], components[5]};
    }

    Vector2D getPosAsVector() const {
        return Vector2D(components[2], components[5]);
    }

    // getters

    [[nodiscard]] float& at(std::byte row, std::byte column) const {
        return components[row * 3 + column];
    }

    Matrix3f operator*(const float& scalar) const {
        return Matrix3f(
            components[0] * scalar, components[1] * scalar, components[2] * scalar,
            components[3] * scalar, components[4] * scalar, components[5] * scalar,
            components[6] * scalar, components[7] * scalar, components[8] * scalar);
    }

    Matrix3f operator*=(const float& scalar) const {
        return *this * scalar;
    }

    Matrix3f operator/(const float& scalar) const {
        return Matrix3f(
            components[0] / scalar, components[1] / scalar, components[2] / scalar,
            components[3]/scalar, components[4]/scalar, components[5]/scalar,
            components[6] / scalar, components[7] / scalar, components[8] / scalar);
    }

    Matrix3f operator/=(const float& scalar) const {
        return *this / scalar;
    }

    Matrix3f operator+(const Matrix3f& other) const {
        return Matrix3f(
            components[0] + other.components[0], components[1] + other.components[1], components[2] + other.components[2],
            components[3] + other.components[3], components[4] + other.components[4], components[5] + other.components[5],
            components[6] + other.components[6], components[7] + other.components[7], components[8] + other.components[8]);
    }

    Matrix3f operator+=(const Matrix3f& other) const {
        return *this + other;
    }

    Matrix3f operator-(const Matrix3f& other) const {
        return Matrix3f(
            components[0] - other.components[0], components[1] - other.components[1], components[2] - other.components[2],
            components[3] - other.components[3], components[4] - other.components[4], components[5] - other.components[5],
            components[6] - other.components[6], components[7] - other.components[7], components[8] - other.components[8]);
    }



    Vector3D transformVec3(const Vector3D& vec) const {
        return Vector3D(components[0] * vec.x + components[1] * vec.y + components[2] * vec.z,
                        components[3] * vec.x + components[4] * vec.y + components[5] * vec.z,
                          vec.z);
    }

    Vector2D transformVec2(const Vector2D& vec) const {
        return Vector2D(components[0] * vec.x + components[1] * vec.y,
                        components[3] * vec.x + components[4] * vec.y);
    }

    Vector2D operator*(const Vector2D& vec) const {
        return transformVec2(vec);
    }

    Vector2D operator*=(const Vector2D& vec) const {
        return *this * vec;
    }

    Matrix3f move(const Vector2D& vector2_d) const {
        
    }







};

#endif //MATHLIB_MAIN_MATRIX3F_H
