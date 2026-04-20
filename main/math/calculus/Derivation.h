#ifndef DERIVATION_H
#define DERIVATION_H
#include "math/curves/Curve.h"
#include "math/vectors/AbstractVector.h"

class Derivation {

public:

    static const float& dx = 0.001;

    static const float& divisor = dx * 2;

    static float deriveSingleVariableFunction(const float& a) {
        return 0f;
    }

    template<int dim>
    static AbstractVector<dim> deriveCurve(const float& t, const Curve<dim>& curve) {
        return (curve.getPoint(t + dx) - curve.getPoint(t - dx)) / divisor;
    }


};



#endif