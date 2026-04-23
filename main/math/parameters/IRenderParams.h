//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_IRENDERPARAMS_H
#define MATHLIB_MAIN_IRENDERPARAMS_H
#include <cstdint>

class RenderParams {

public:


    const int8_t reflection, refraction, brightness;

    RenderParams(const int8_t& reflection_, const int8_t& refraction_, const int8_t& brightness_)
    : reflection(reflection_), refraction(refraction_), brightness(brightness_) {}

    float getReflection() const {
        return reflection;
    }

    float getRefraction() const {
        return refraction;
    }

    float getBrightness() const {
        return brightness;
    }
};

#endif //MATHLIB_MAIN_IRENDERPARAMS_H
