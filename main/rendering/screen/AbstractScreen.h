#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H
#include "math/vectors/AbstractVector.h"
#include "math/curves/Curve.h"

#include <atomic>
#include <thread>

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

    virtual void loop() = 0;


    void renderTriangle(const AbstractVector<dim>& vec1, const AbstractVector<dim>& vec2, const AbstractVector<dim>& vec3) const;

    void renderRectangle(const AbstractVector<dim>& vec1, const AbstractVector<dim>& vec2) const;

    void renderCurve(const Curve<dim>& curve, const int& nodes) const;

};

#endif
