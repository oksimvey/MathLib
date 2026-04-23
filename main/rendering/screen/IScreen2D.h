//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_ISCREEN2D_H
#define MATHLIB_MAIN_ISCREEN2D_H
#include "IScreen.h"

class IScreen2D : public IScreen {

    public:

    float angle;

    float zoom;

    Vector2D position;

    Vector2D toScreen(const Vector2D& world) const {
        return (world - position) * zoom;
    }

    void render() override {

    }
};

#endif //MATHLIB_MAIN_ISCREEN2D_H
