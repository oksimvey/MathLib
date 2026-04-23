//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_RENDERABLE2DINSTANCE_H
#define MATHLIB_MAIN_RENDERABLE2DINSTANCE_H
#include "IRenderableInstance.h"
#include "Renderable2DVertexState.h"
#include "math/vectors/Vector2D.h"

template<int nodes>
class Renderable2DInstance : public IRenderableInstance {


    float rotation;

public:


    std::array<Renderable2DVertexState, nodes> vertices;

    Vector2D position;


    Renderable2DInstance(float rot0, Vector2D pos) : rotation(rot0), position(pos) {
    }

    Renderable2DVertexState worldPosition(const int& index) const  {
        return Renderable2DVertexState(vertices[index].x + position.x, vertices[index].y + position.y, vertices[index].col);
    }

    Renderable2DVertexState getVertex(const int& index) const {
        return vertices[index];
    }

    void setVertex(const int& index,
                   const float& x,
                   const float& y,
                   ConstantColorParam color_) {
        vertices[index] = Renderable2DVertexState(x, y, color_);
    }


    float getRotation() const {
        return rotation;
    }

    void setRotation(const float& angle) {
        rotate(angle - rotation);
    }

    void rotate(const float& angle) {
        if (angle == 0) return;
        rotation += angle;
        updateRotation(angle);
    }

private:

    void updateRotation(const float& angle) {
        for (int i = 0; i < nodes; i++) {
            vertices[i] = vertices[i].rotate(angle);
        }
    }

};

#endif //MATHLIB_MAIN_RENDERABLE2DINSTANCE_H
