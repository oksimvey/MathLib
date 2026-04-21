#include <glad/glad.h>

#include "math/transformations/LinearTransformation.h"
#include "rendering/screen/Screen2D.h"
#include <cmath>
#include <iostream>



int main() {

    auto screen2_d = Screen2D(800, 600, AbstractVector<2>(0,0));

    screen2_d.init();

    screen2_d.addLine(Line(-100, 0, 100, 0, 1, 1, 1, 1, 5));
    screen2_d.addLine(Line(0, -100, 0, 100, 1, 1, 1, 1, 5));

    for (int i = -25; i < 25; i++) {
        screen2_d.addLine(Line(i, -0.1f, i, 0.1f, 1, 1, 1, 1, 5));
        screen2_d.addLine(Line(-0.1f, i, 0.1f, i, 1, 1, 1, 1, 5));
    }

    auto curve = Curve<2>(0, M_PI*2, 100);

    curve.getPoint = [](const float t) {
        return AbstractVector<2>{cos(t), sin(t)};
    };

    curve.getColor = [](float t) -> std::array<float, 4> {
        float p = t / (M_PI * 4);
        return std::array<float, 4>{0.75, 0.33f + p,1, 1};
    };

    screen2_d.addCurve(curve);

    screen2_d.loop();





    return 0;
}