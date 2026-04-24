//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_RENDERABLE2DCURVE_H
#define MATHLIB_MAIN_RENDERABLE2DCURVE_H
#include "Renderable2DInstance.h"
#include "math/curves/ICurve.h"

template<int nodes>

class Renderable2DCurve : public Renderable2DInstance<nodes> {

    ICurve<2> curve;

public:

    Renderable2DCurve(const ICurve<2>& curve, Renderable2DInstance<nodes> instance) : Renderable2DInstance<nodes>(instance), curve(curve) {}

    void generate() {
        for (int i = 0; i < nodes; i++) {
            const float& t = curve.t0 + (curve.T.endValue - curve.t0) * static_cast<float>(i) / static_cast<float>(nodes);
            const float& x = curve.getPoint(t)[0];
            const float& y = curve.getPoint(t)[1];
            this -> setVertex(i, x, y, curve.getColor(t));
        }
    }

    static int getNodes() {
        return nodes;
    }


};



#endif //MATHLIB_MAIN_RENDERABLE2DCURVE_H
