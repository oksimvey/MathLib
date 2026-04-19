#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "AbstractVector.h"

class Vector2D : public AbstractVector<2> {

    public:

    Vector2D(const float x, const float y) {
        components[0] = x;
        components[1] = y;
    }

    Vector2D() : Vector2D(0, 0) {
    }

    explicit Vector2D(const ComplexNumber number) {
        components[0] = number.real();
        components[1] = number.imag();
    }




};

#endif