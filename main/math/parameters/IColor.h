//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_ICOLOR_H
#define MATHLIB_MAIN_ICOLOR_H

class IColor {
public:
    IColor() = default;

    virtual float getRed() const;

    virtual float getGreen() const;

    virtual float getBlue() const;
    
    virtual float getAlpha() const;
};

#endif //MATHLIB_MAIN_ICOLOR_H
