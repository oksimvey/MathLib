#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H
#include "math/vectors/AbstractVector.h"
#include "math/curves/Curve.h"

class AbstractScreen {

    AbstractScreen(int widht, int height, AbstractVector pos);

    void init() const;

    void renderLine(const AbstractVector& vec1, const AbstractVector& vec2) const;

    void renderTriangle(const AbstractVector& vec1, const AbstractVector& vec2, const AbstractVector& vec3) const;

    void renderRectangle(const AbstractVector& vec1, const AbstractVector& vec2) const;

    void renderCurve(const Curve& curve) const;
    

};

#endif
