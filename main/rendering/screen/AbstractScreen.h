#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H
#include "math/vectors/AbstractVector.h"
#include "math/curves/Curve.h"

template <int dim>
class AbstractScreen {

public:

    std::vector<Line> lines;

        int width_, height_;
        AbstractVector<dim> position;

        AbstractScreen(int width, int height, AbstractVector<dim> pos)
            : width_(width), height_(height), position(pos) {}

        virtual void init() = 0;


    virtual void renderLine(const Line& line) = 0;

    void addLine(const Line& line) {
        lines.push_back(line);
    }


    void renderTriangle(const AbstractVector<dim>& vec1, const AbstractVector<dim>& vec2, const AbstractVector<dim>& vec3) const;

    void renderRectangle(const AbstractVector<dim>& vec1, const AbstractVector<dim>& vec2) const;

    void renderCurve(const Curve<dim>& curve, const int& nodes) const;

};

#endif
