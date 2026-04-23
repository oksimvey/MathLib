//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_ICOLOR_H
#define MATHLIB_MAIN_ICOLOR_H
#include "TimeParameter.h"

#include <array>
#include <cstdint>

class IColor {

    cont std::array<TimeParameter<uint8_t>, 4> color;

public:

    IColor() = default;

    IColor(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a)
        : color({constantTimeParam(r), constantTimeParam(g), constantTimeParam(b), constantTimeParam(a)}){}

    IColor(const TimeParameter<uint8_t>& r, const TimeParameter<uint8_t>& g, const TimeParameter<uint8_t>& b, const TimeParameter<uint8_t>& a)
    : color({r, g, b, a}) {}

    uint8_t getRed(const float& time) const {
        if (colorDynamic.empty()) {
            return colorFixed[0];
        }
        return colorDynamic[0].getCurrentValue(time);
    }

    uint8_t getGreen(const float& time) const {
        if (colorDynamic.empty()) {
            return colorFixed[1];
        }
        return colorDynamic[1].getCurrentValue(time);
    }

    uint8_t getBlue(const float& time) const {
        if (colorDynamic.empty()) {
            return colorFixed[2];
        }
        return colorDynamic[2].getCurrentValue(time);
    }
    
    uint8_t getAlpha(const float& time) const {
        if (colorDynamic.empty()) {
            return colorFixed[3];
        }
        return colorDynamic[3].getCurrentValue(time);
    }
};

#endif //MATHLIB_MAIN_ICOLOR_H
