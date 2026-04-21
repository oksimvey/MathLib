#ifndef MATHLIB_MAIN_SCREEN3D_H
#define MATHLIB_MAIN_SCREEN3D_H
#include "AbstractScreen.h"
#include "math/transformations/LinearTransformation.h"
#include "math/vectors/AbstractVector.h"

class Screen3D : public AbstractScreen<3>{

public:


    LinearTransformation<3, 3> camOrientation = identity<3>;

    float cameraDistance = 1;

   AbstractVector<3> camPosition = AbstractVector<3> ();

    void move(const AbstractVector<3>& vec) {;
        camPosition = camPosition + vec;
    }

    void translate(const AbstractVector<3>& vec) {
        camposition = camposition + camOrientation * vec;
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

    std::array<float, 2> projectVertex(const AbstractVector<3>& vertex) {

    const auto& basis = camOrientation.getBasis();

    // camera basis vectors:
    // forward = direction the camera is looking at
    // right = horizontal direction of the screen
    // up = vertical direction of the screen
    const AbstractVector<3>& forward = basis[0];
    const AbstractVector<3>& right   = basis[1];
    const AbstractVector<3>& up      = basis[2];

    // the screen plane is centered at:
    // camPosition + forward * distanceToCam
    //
    // and its equation is:
    // forward · (X - screenCenter) = 0
    //
    // where X is any point on the screen plane

    // the line from the camera to the vertex is:
    // L(t) = camPosition + t(vertex - camPosition)
    //
    // substitute this in the plane equation:
    //
    // forward · (camPosition + t(vertex - camPosition) - screenCenter) = 0
    //
    // since screenCenter = camPosition + forward * distanceToCam:
    //
    // forward · (t(vertex - camPosition) - forward * distanceToCam) = 0
    //
    // distributing the dot product:
    //
    // t(forward · (vertex - camPosition)) - distanceToCam(forward · forward) = 0
    //
    // assuming forward is normalized:
    //
    // forward · forward = 1
    //
    // so:
    //
    // t(forward · (vertex - camPosition)) = distanceToCam
    //
    // therefore:
    //
    // t = distanceToCam / (forward · (vertex - camPosition))

    const float& denom = forward * (vertex - camPosition);

    // if denom == 0, the line is parallel to the screen plane, so there is no valid intersection
    if (std::abs(denom) < 1e-6f)
        return {NAN, NAN};

    float t = distanceToCam / denom;

    // if t <= 0, the intersection lies behind the camera, meaning the vertex is not visible
    if (t <= 0)
        return {NAN, NAN};

    // now compute the intersection point with the screen plane
    AbstractVector<3> intersectionPoint = camPosition + (vertex - camPosition) * t;

    // the center of the screen plane
    AbstractVector<3> screenCenter = camPosition + forward * distanceToCam;

    // vector from the screen center to the projected point
    AbstractVector<3> screenVector = intersectionPoint - screenCenter;

    // now we express screenVector in the screen basis:
    //
    // screenVector = x * right + y * up
    //
    // since right and up are orthonormal basis vectors:
    //
    // x = screenVector · right
    // y = screenVector · up
    //
    // these are the 2D screen coordinates of the projected point

    const float& x = screenVector * right;
    const float& y = screenVector * up;

    return {x, y};

}




    Screen3D(const int w, const int h, const std::array<TimeParameter, 4>& params, const AbstractVector<3> pos) : AbstractScreen(w, h, params) {
        camPosition = pos;
    }




};

#endif //MATHLIB_MAIN_SCREEN3D_H
