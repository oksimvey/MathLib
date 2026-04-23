//
// Created by hapoe on 4/22/2026.
//

#ifndef MATHLIB_MAIN_RENDERABLE2DOBJECT_H
#define MATHLIB_MAIN_RENDERABLE2DOBJECT_H
#include "Renderable2DFrag.h"

#include <array>

template <int cells>
class Renderable2DObject {

public:

    std::array<Renderable2DFrag, cells> parts;

    Renderable2DObject() = default;

};

#endif //MATHLIB_MAIN_RENDERABLE2DOBJECT_H
