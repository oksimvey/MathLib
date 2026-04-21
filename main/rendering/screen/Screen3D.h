//
// Created by hapoe on 4/20/2026.
//

#ifndef MATHLIB_MAIN_SCREEN3D_H
#define MATHLIB_MAIN_SCREEN3D_H
#include "AbstractScreen.h"
#include "math/transformations/LinearTransformation.h"
#include "math/vectors/Vector3D.h"

class Screen3D : public AbstractScreen<3>{

public:


    LinearTransformation<3, 3> camOrientation = LinearTransformation<3, 3>;

    Vector3D camPosition = Vector3D();

    void moveCam(const Vector3D& vec) {
        camPosition = camPosition + vec;
    }

    void rotateCamInXAxis(const float& angle) {
        camOrientation = rotationInXAxis(angle) * camOrientation;
    }

    void rotateCamInYAxis(const float& angle) {
        camOrientation = rotationInYAxis(angle) * camOrientation;
    }

    void rotateCamInZAxis(const float& angle) {
        camOrientation = rotationInZAxis(angle) * camOrientation;
    }




    Screen3D(const int w, const int h, const AbstractVector<3> pos) : AbstractScreen(w, h, pos) {}




};

#endif //MATHLIB_MAIN_SCREEN3D_H
