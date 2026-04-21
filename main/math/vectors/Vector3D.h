//
// Created by hapoe on 4/19/2026.
//

#ifndef MATHLIB_MAIN_VECTOR3D_H
#define MATHLIB_MAIN_VECTOR3D_H

#include "math/vectors/AbstractVector.h"

class Vector3D : public AbstractVector<3> {

public:

    Vector3D(const float x, const float y, const float z) {
        components[0] = x;
        components[1] = y;
        components[2] = z;
    }

    Vector3D() : Vector3D(0, 0, 0) {
    }

    float x() const {
        return components[0];
    }

    float y() const {
        return components[1];
    }

    float z() const {
        return components[2];
    }

    void setX(const float& x) {
        components[0] = x;
    }

    void setY(const float& y) {
        components[1] = y;
    }

    void setZ(const float& z) {
        components[2] = z;
    }

};

#endif //MATHLIB_MAIN_VECTOR3D_H
