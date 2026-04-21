#include <glad/glad.h>

#include "math/transformations/LinearTransformation.h"
#include "rendering/screen/Screen2D.h"
#include <cmath>

#include <GLFW/glfw3.h>

#include "math/parameters/TimeParameter.h"
#include "math/easing/EasingStyle.h"

int main() {

    auto screen2_d = Screen2D(800, 600,
        {constantTimeParam(0.1), constantTimeParam(0.1), constantTimeParam(0.15), constantTimeParam(1)}, AbstractVector<2>(0,0));

    screen2_d.init();

    screen2_d.addLine(Line(-100, 0, 100, 0, 1, 1, 1, 1, 5));
    screen2_d.addLine(Line(0, -100, 0, 100, 1, 1, 1, 1, 5));

    for (int i = -25; i < 25; i++) {
        screen2_d.addLine(Line(i, -0.1f, i, 0.1f, 1, 1, 1, 1, 1));
        screen2_d.addLine(Line(-0.1f, i, 0.1f, i, 1, 1, 1, 1, 1));
    }

    const auto param = TimeParameter(false,false,  5.0f, -M_PI/2, M_PI*3/2,Easing::InOut, glfwGetTime(), 0);

    const std::vector parameters = {TimeParameter(false,false, 5.0f, 0, 1, Easing::InOut, glfwGetTime(), 5.0f)};

    auto curve = Curve<2>(-M_PI/2, param, 250, parameters);

    curve.getPoint = [&](const float t) {
        float s = curve.parameters[0].getCurrentValue(glfwGetTime());
        AbstractVector<2> polar = AbstractVector<2>(cos(4*t)*cos(t), cos(4*t)*sin(t));
        return AbstractVector<2>{ cos(t), sin(t)} * (1 - s) + polar * s;
    };

    curve.getColor = [](float t) -> std::array<float, 4> {
        float p = std::abs(sin(t*10));
        float s = std::abs(sin(t*100));
        return std::array<float, 4>{0.5f - p/2 ,0.25f+ p, 0.25f + s, 1};
    };

    screen2_d.addCurve(curve);

    screen2_d.loop();





    return 0;
}