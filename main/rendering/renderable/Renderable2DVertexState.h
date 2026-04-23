//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_RENDERABLE2DVERTEXSTATE_H
#define MATHLIB_MAIN_RENDERABLE2DVERTEXSTATE_H
#include "math/parameters/IColor.h"
#include <cmath>

class Renderable2DVertexState {

    public:

    float x;
    float y;
     ConstantColorParam col;

    Renderable2DVertexState()
        : x(0.0f), y(0.0f), col(255, 255, 255, 255) {}



    Renderable2DVertexState(const float& x_, const float& y_, const ConstantColorParam col_) : x(x_), y(y_), col(col_) {}

    Renderable2DVertexState rotate(const float& angle) const {
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);
        return Renderable2DVertexState(x * cos - y * sin , y * cos + x * sin, col);
    }

};

#endif //MATHLIB_MAIN_RENDERABLE2DVERTEXSTATE_H
