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

    float x() const {
        return components[0];
    }

    float y() const {
        return components[1];
    }

    void setX(const float& x) {
        components[0] = x;
    }

    void setY(const float& y) {
        components[1] = y;
    }




};

#endif