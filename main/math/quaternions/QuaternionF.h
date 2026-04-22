#ifndef QUATERNIONF_H
#define QUATERNIONF_H

#include <cmath>
#include "math/vectors/Vector3D.h"

class QuaternionF {
public:

    const float a, b, c, d;

    QuaternionF() : a(1), b(0), c(0), d(0) {}

    QuaternionF(float a, float b, float c, float d)
        : a(a), b(b), c(c), d(d) {}

    QuaternionF operator*(const QuaternionF& q) const {
        return QuaternionF(
            a*q.a - b*q.b - c*q.c - d*q.d,
            a*q.b + b*q.a + c*q.d - d*q.c,
            a*q.c - b*q.d + c*q.a + d*q.b,
            a*q.d + b*q.c - c*q.b + d*q.a
        );
    }

    QuaternionF conjugate() const {
        return QuaternionF(a, -b, -c, -d);
    }

    QuaternionF normalized() const {
        const float& mag = std::sqrt(a*a + b*b + c*c + d*d);
        return QuaternionF(a/mag, b/mag, c/mag, d/mag);
    }

    Vector3D rotateVector(const Vector3D& v) const {
        const Vector3D& u(b, c, d);

        const Vector3D& uv = u ^ v;
        const Vector3D& uuv = u ^ uv;

        return v + uv * (2.0f * a) + uuv * 2.0f;
    }

    QuaternionF rotateXAxis(const float angle) const {
        const float s = std::sin(angle * 0.5f);
        const float c0 = std::cos(angle * 0.5f);

        return QuaternionF(
            c0*a - s*b,
            c0*b + s*a,
            c0*c - s*d,
            c0*d + s*c
        );
    }

    QuaternionF rotateYAxis(const float angle) const {
        const float s = std::sin(angle * 0.5f);
        const float c0 = std::cos(angle * 0.5f);

        return QuaternionF(
            c0*a - s*c,
            c0*b + s*d,
            c0*c + s*a,
            c0*d - s*b
        );
    }

    QuaternionF rotateZAxis(const float angle) const {
        const float s = std::sin(angle * 0.5f);
        const float c0 = std::cos(angle * 0.5f);

        return QuaternionF(
            c0*a - s*d,
            c0*b - s*c,
            c0*c + s*b,
            c0*d + s*a
        );
    }
};

#endif