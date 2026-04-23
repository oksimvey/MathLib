#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H
#include "math/vectors/AbstractVector.h"
#include "math/curves/Curve.h"
#include "math/parameters/TimeParameter.h"

#include <GLFW/glfw3.h>

template <int dim>
class AbstractScreen {

public:

    std::vector<Line> lines;

    std::vector<Curve<dim>> curves;

    std::array<TimeParameter<float>, 4> screencol;

    int width_, height_;

    AbstractScreen(const int width, const int height, const std::array<TimeParameter<float>, 4>& color)
            : screencol(color), width_(width), height_(height) {}



    virtual void init() = 0;


    virtual void renderLine(const Line& line) = 0;

    void addLine(const Line& line) {
        lines.push_back(line);
    }

    void addCurve(const Curve<dim>& curve) {
        curves.push_back(curve);
    }

    virtual void loop() = 0;

    virtual float getLodFactor() const = 0;

    std::array<float, 2> projectVertex(const AbstractVector<dim>& vec) const;

    void renderTriangle(const AbstractVector<dim>& vec1, const AbstractVector<dim>& vec2, const AbstractVector<dim>& vec3) const;

    void renderRectangle(const AbstractVector<dim>& vec1, const AbstractVector<dim>& vec2) const;

    void renderCurve(const Curve<dim>& curve) {

        const int nodes = curve.nodes *(1 - getLodFactor());

        float time = glfwGetTime();


        for (int i = 0; i < nodes; i++) {
            const float t1 = curve.t0 + (curve.getT(time) - curve.t0) * static_cast<float>(i) / static_cast<float>(nodes);
            const float t2 = curve.t0 + (curve.getT(time) - curve.t0) * static_cast<float>(i + 1) / static_cast<float>(nodes);
            float x = curve.getPoint(t1).getComponents()[0];
            float y = curve.getPoint(t1).getComponents()[1];
            float x2 = curve.getPoint(t2).getComponents()[0];
            float y2 = curve.getPoint(t2).getComponents()[1];



            renderLine(Line(x, y, x2, y2,
                curve.getColor(t1)[0], curve.getColor(t1)[1], curve.getColor(t1)[2], curve.getColor(t1)[3], 5));

        }
    }

};

#endif
