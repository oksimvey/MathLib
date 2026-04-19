// MathUtils.h
#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace MathUtils {

    constexpr float EPS = 1e-6f;

    bool isNearZero(float x);

    bool areEqual(float a, float b);
}

#endif