#include <cmath>

#include "math/parameters/ConstantColorParam.h"
#include "rendering/screen/IScreen2D.h"

int main() {

    ConstantColorParam screen_color = ConstantColorParam(25, 25, 40, 255);

    IScreen2D screen2_d = IScreen2D(600, 800, screen_color, Vector2D(0,0));

    ICurve<2> curvebase = ICurve<2>(0, constantTimeParam<float>(2*M_PI));

    curvebase.getPoint = [](float t) {
        return std::array<float, 2>({std::cos(t), std::sin(t)});
    };

    curvebase.getColor = [](float t) {
        return ConstantColorParam(155 + 100*std::sin(3*t), 155, 155 - 100 * std::cos(2*t), 255);
    };

    Renderable2DInstance<250> instance = Renderable2DInstance<250>(0, Vector2D(0,0));

    Renderable2DCurve<250> curve = Renderable2DCurve<250>(curvebase, instance);

    curve.generate();


    screen2_d.curves.push_back(curve);

    screen2_d.init();



    return 0;
}