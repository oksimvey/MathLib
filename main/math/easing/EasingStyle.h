//
// Created by hapoe on 4/20/2026.
//

#ifndef MATHLIB_MAIN_EASINGSTYLE_H
#define MATHLIB_MAIN_EASINGSTYLE_H

#include <cmath>

struct Easing {

    enum EasingType {
        In,
        Out,
        InOut,
        Linear,
        Quadratic,
        Cubic

    };

    static float interpolate(const EasingType& op, const float& dt) {
        switch (op) {

        case Linear:    return dt;
        case Quadratic: return dt * dt;
        case Cubic:     return dt * dt * dt;

        case In:        return 1 - std::cos(M_PI * dt / 2);
        case Out:       return std::sin(M_PI * dt / 2);
        case InOut:     return (1 - std::cos(M_PI * dt)) / 2;
        }
        return 0.0f;
    }
};


#endif //MATHLIB_MAIN_EASINGSTYLE_H
