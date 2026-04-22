//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_CONSTANTRENDERPARAMS_H
#define MATHLIB_MAIN_CONSTANTRENDERPARAMS_H
#include "IRenderParams.h"

#include <cstdint>

class ConstantRenderParams : public IRenderParams {

    public:

    const int8_t reflection, refraction, brightness;

    ConstantRenderParams(const int8_t& reflection_, const int8_t& refraction_, const int8_t& brightness_) : reflection(reflection_), refraction(refraction_), brightness(brightness_) {}

    float getReflection() const {
        constexpr int8_t i = 2000;
        return i;
    }

    float getRefraction() const {
        return refraction;
    }

    float getBrightness() const {
        return brightness;
    }

};

#endif //MATHLIB_MAIN_CONSTANTRENDERPARAMS_H
