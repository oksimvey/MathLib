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

    TimeParameter<float> T;

    int nodes;

    std::vector<TimeParameter<float>> parameters;

    Curve(float t0, const TimeParameter<float>& parameter_, int nodes, const std::vector<TimeParameter<float>>& params) : T(parameter_), parameters(params) {
        this->t0 = t0;
        this->nodes = nodes;
    }

    float getT(const float& time) const {
        return T.getCurrentValue(time);
    }


    std::function<AbstractVector<dim>(float)> getPoint;

    std::function<std::array<float,4>(float)> getColor;






};

#endif