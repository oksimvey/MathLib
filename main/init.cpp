#include "math/parameters/ConstantColorParam.h"
#include "rendering/screen/IScreen2D.h"

int main() {

    ConstantColorParam screen_color = ConstantColorParam(25, 25, 40, 255);

    IScreen2D screen2_d = IScreen2D(600, 800, screen_color, Vector2D(0,0));

    screen2_d.init();



    return 0;
}