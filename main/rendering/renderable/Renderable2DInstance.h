//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_RENDERABLE2DINSTANCE_H
#define MATHLIB_MAIN_RENDERABLE2DINSTANCE_H
#include "IRenderableInstance.h"
#include "math/vectors/Vector2D.h"

class Renderable2DInstance : public IRenderableInstance {

    public:

    Vector2D position;

    float rotation;

    uint8_t layer;

    Renderable2DInstance() = default;

    void Vector2D getRealWorldVertex() override {

    }
};

#endif //MATHLIB_MAIN_RENDERABLE2DINSTANCE_H
