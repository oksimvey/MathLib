//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_RENDERABLE2DVERTEXSTATE_H
#define MATHLIB_MAIN_RENDERABLE2DVERTEXSTATE_H
#include <cmath>

class Renderable2DVertexState {

    public:

    float x;
    float y;

    uint8_t r, g, b, a;

    Renderable2DVertexState()
        : x(0.0f), y(0.0f), r(255), g(255), b(255), a(255) {}


    Renderable2DVertexState(const float& x_, const float& y_) : x(x_), y(y_), r(255), g(255), b(255), a(255) {}

    Renderable2DVertexState(const float& x_, const float& y_, const ConstantColorParam& color) : x(x_), y(y_), r(color.getRed()), g(color.getGreen()), b(color.getBlue()), a(color.getAlpha()) {}

    Renderable2DVertexState rotate(const float& angle) const {
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);
        return Renderable2DVertexState(x * cos - y * sin , y * cos + x * sin);
    }
    void updateColor(const uint8_t& r_, const uint8_t& g_, const uint8_t& b_, const uint8_t& a_) {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }

    void updateColor(const ConstantColorParam& color) {
        r = color.getRed();
        g = color.getGreen();
        b = color.getBlue();
        a = color.getAlpha();
    }

    uint8_t getRed() const {
        return r;
    }

    uint8_t getGreen() const {
        return g;
    }

    uint8_t getBlue() const {
        return b;
    }

    uint8_t getAlpha() const {
        return a;
    }

};

#endif //MATHLIB_MAIN_RENDERABLE2DVERTEXSTATE_H
