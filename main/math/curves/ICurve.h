//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_ICURVE_H
#define MATHLIB_MAIN_ICURVE_H
#include "math/parameters/IColor.h"
#include "math/parameters/TimeParameter.h"
#include "math/vectors/Vector2D.h"

#include <functional>

template<int dimension>
class ICurve {

public:

    float t0;

    TimeParameter<float> T;

    ICurve(float t0, TimeParameter<float> time_parameter): t0(t0), T(time_parameter) {}

    float getT(const float& time) const {
        return T.getCurrentValue(time);
    }

    std::function<std::array<float, dimension>(float)> getPoint;

    std::function<ConstantColorParam()> getColor;

};

#endif //MATHLIB_MAIN_ICURVE_H
