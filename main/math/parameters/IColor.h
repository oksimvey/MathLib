//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_ICOLOR_H
#define MATHLIB_MAIN_ICOLOR_H
#include "TimeParameter.h"

#include <array>
#include <cstdint>
#include <memory>
class IColor {

public:


    virtual uint8_t getRed(const float& time) const = 0;

    virtual uint8_t getGreen(const float& time) const = 0;

    virtual uint8_t getBlue(const float& time) const = 0;

    virtual uint8_t getAlpha(const float& time) const = 0;
};

#endif //MATHLIB_MAIN_ICOLOR_H
