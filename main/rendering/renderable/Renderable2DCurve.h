//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_RENDERABLE2DCURVE_H
#define MATHLIB_MAIN_RENDERABLE2DCURVE_H
#include "Renderable2DInstance.h"
#include "Renderable2DVertexState.h"
#include "math/curves/Curve.h"

class Renderable2DCurve : public Renderable2DInstance {

    int nodes;

    Curve<2> curve;

    std::array<Renderable2DVertexState, nodes> vertices;

    void generate();

    void updateVertices();

    void updateCurvePoints();

    void updateCurvePos();

    void updateCamPos();

    void updateCamZoom();


};



#endif //MATHLIB_MAIN_RENDERABLE2DCURVE_H
