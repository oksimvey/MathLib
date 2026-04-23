//
// Created by hapoe on 4/23/2026.
//

#ifndef MATHLIB_MAIN_CONSTANTCOLORPARAM_H
#define MATHLIB_MAIN_CONSTANTCOLORPARAM_H
#include "IColor.h"

class ConstantColorParam : public IColor {

    const uint8_t color[4];

    public:

       ConstantColorParam() : color{0, 0, 0, 0} {}

        ConstantColorParam(const uint8_t r, const uint8_t g, const uint8_t b,
                         const uint8_t a) : color{r, g, b, a} {}

        uint8_t getRed(const float& time) const override {
            return color[0];
        }

        uint8_t getGreen(const float& time) const override {
            return color[1];
        }

    uint8_t getBlue(const float& time) const override {
        return color[2];
    }

    uint8_t getAlpha(const float& time) const override {
        return color[3];
    }
};

#endif //MATHLIB_MAIN_CONSTANTCOLORPARAM_H
