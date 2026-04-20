#include <glad/glad.h>

#include "math/transformations/LinearTransformation.h"
#include "rendering/screen/Screen2D.h"
#include <cmath>
#include <iostream>

static AbstractVector<2> f(const float x) {
    return AbstractVector<2>(cos(x)+x-M_PI/2,1-sin(2*x));
}

int main() {

    auto screen2_d = Screen2D(800, 600, AbstractVector<2>(0,0));

    screen2_d.init();

    screen2_d.addLine(Line(-100, 0, 100, 0, 1, 1, 1, 1, 5));
    screen2_d.addLine(Line(0, -100, 0, 100, 1, 1, 1, 1, 5));

    float a = -10;
    float b = 10;
    int steps = 100;

    for (int i = 0; i < steps; i++) {
        const float t1 = a + (b - a) * static_cast<float>(i) / static_cast<float>(steps);
        const float t2 = a + (b - a) * static_cast<float>(i + 1) / static_cast<float>(steps);
        float x = f(t1).getComponents()[0];
        float y = f(t1).getComponents()[1];
        float x2 = f(t2).getComponents()[0];
        float y2 = f(t2).getComponents()[1];



        screen2_d.addLine(Line(x, y, x2, y2, 1, 1, 1, 1, 5));

    }
    screen2_d.loop();





    return 0;
}