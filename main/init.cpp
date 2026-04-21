#include <glad/glad.h>

#include "math/transformations/LinearTransformation.h"
#include "rendering/screen/Screen2D.h"
#include <cmath>
#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include "math/parameters/TimeParameter.h"
#include "math/easing/EasingStyle.h"
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

    const auto param = TimeParameter(true,  7.5f, 0, M_PI * 2,Easing::InOut, glfwGetTime(), 0);

    auto curve = Curve<2>(0, param, 250);

    curve.getPoint = [](const float t) {
        return AbstractVector<2>{cos(2*t)*cos(t),cos(2*t)* sin(t)};
    };

    curve.getColor = [](float t) -> std::array<float, 4> {
        float p = std::abs(sin(t*10));
        return std::array<float, 4>{0.5f - p/2 ,0.25f+ p, 1, 1};
    };

    screen2_d.addCurve(curve);

    screen2_d.loop();





    return 0;
}