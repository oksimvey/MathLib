#ifndef CURVE_H
#define CURVE_H

#include "math/vectors/AbstractVector.h"

#include <array>

#include <functional>

template <int dim>
class Curve {

    public:

    float t0, t1;

    int nodes;

    Curve(float t0, float t1, int nodes) {
        this->t0 = t0;
        this->t1 = t1;
        this->nodes = nodes;
    }


    std::function<AbstractVector<dim>(float)> getPoint;
    std::function<std::array<float,4>(float)> getColor;






};

#endif