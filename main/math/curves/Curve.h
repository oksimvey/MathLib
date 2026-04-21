#ifndef CURVE_H
#define CURVE_H

#include "math/parameters/TimeParameter.h"
#include "math/vectors/AbstractVector.h"

#include <array>

#include <functional>

template <int dim>
class Curve {

    public:
     float t0;

    TimeParameter parameter;

    int nodes;

    Curve(float t0, const TimeParameter& parameter_, int nodes) : parameter(parameter_) {
        this->t0 = t0;
        this->nodes = nodes;
    }

    float getT(const float& time) const {
        return parameter.getCurrentValue(time);
    }


    std::function<AbstractVector<dim>(float)> getPoint;

    std::function<std::array<float,4>(float)> getColor;






};

#endif