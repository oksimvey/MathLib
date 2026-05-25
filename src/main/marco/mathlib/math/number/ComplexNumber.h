#ifndef MATHLIB_COMPLEXNUMBER_H
#define MATHLIB_COMPLEXNUMBER_H

#include "RealNumber.h"
#include "Scalar.h"

class ComplexNumber : public Scalar {

    public:

        const RealNumber real;

        const RealNumber imag;

        ComplexNumber(RealNumber real, RealNumber imag) : real(real), imag(imag) {}

        ComplexNumber operator+(const ComplexNumber& other) const {
            return ComplexNumber(real + other.real, imag + other.imag);
        }

};

#endif 