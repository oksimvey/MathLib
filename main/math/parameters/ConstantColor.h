//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_CONSTANTCOLOR_H
#define MATHLIB_MAIN_CONSTANTCOLOR_H

#include "math/parameters/IColor.h"

class ConstantColor : public IColor {

    const float& red, green, blue, alpha;

    public:

    ConstantColor(const float& red_, const float& green_, const float& blue_, const float& alpha_) : red(red_), green(green_), blue(blue_), alpha(alpha_) {}

    float getRed() const override {
        return red;
    }

    float getGreen() const override {
        return green;
    }

    float getBlue() const override {
        return blue;
    }

    float getAlpha() const override {
        return alpha;
    }
};

#endif //MATHLIB_MAIN_CONSTANTCOLOR_H
