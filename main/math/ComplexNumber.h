#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <cmath>

#include <string>

#include <iostream>

#include "math/MathUtils.h"

#include "math/vectors/Vector2D.h"

class ComplexNumber {

  private:
    // real and imaginary parts
    float real_;
    float imag_;

  public:
    // constructors
    ComplexNumber(float real, float imag) : real_(real), imag_(imag) {
    }

    ComplexNumber(const ComplexNumber& number) = default;

    ComplexNumber() : ComplexNumber(0, 0){};

    // getters
    float real() const {
        return real_;
    }

    float imag() const {
        return imag_;
    }

    // mod by Pythagoras sqrt(a^2 + b^2)
    float mod() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }

    // takes the angle the point (a, b) forms with x axis from arctan
    float arg() const {
        return std::atan2(imag_, real_);
    }

    // complex number with negative imag part
    ComplexNumber conjugate() const {
        return ComplexNumber(real_, -imag_);
    }

    // takes the square root by doing z^(1/2)
    ComplexNumber sqrt() const {

        if (*this == 0)
            return ComplexNumber(0, 0);
        return *this ^ (ComplexNumber(0.5, 0));
    }

    // basic operations
    ComplexNumber operator+(const ComplexNumber& o) const {
        return ComplexNumber(real_ + o.real_, imag_ + o.imag_);
    }

    ComplexNumber operator+(const float& scalar) const {
        return ComplexNumber(real_ + scalar, imag_);
    }

    ComplexNumber operator-(const ComplexNumber& o) const {
        return ComplexNumber(real_ - o.real_, imag_ - o.imag_);
    }

    ComplexNumber operator-(const float& scalar) const {
        return ComplexNumber(real_ - scalar, imag_);
    }

    ComplexNumber operator-() const {
        return *this * (-1);
    }

    // multiply from (a + bi)(c + di) = ac + adi + cbi + bdi^2 = ac - bd + i(ad
    // + cb)
    ComplexNumber operator*(const ComplexNumber& o) const {
        return ComplexNumber(real_ * o.real_ - imag_ * o.imag_,
                             real_ * o.imag_ + imag_ * o.real_);
    }

    ComplexNumber operator*(const float& scalar) const {
        return ComplexNumber(scalar * real_, scalar * imag_);
    }

    // from (a + bi)/(c + di) = (a+bi)(c-di)/(c+di)(c-di) = ((ac + bd) + i(bc -
    // ad))/(c^2 + d^2)
    ComplexNumber operator/(const ComplexNumber& o) const {
        float denom = o.real_ * o.real_ + o.imag_ * o.imag_;

        if (MathUtils::isNearZero(denom))
            throw std::runtime_error("Division by zero");

        return ComplexNumber((real_ * o.real_ + imag_ * o.imag_) / denom,
                             (imag_ * o.real_ - real_ * o.imag_) / denom);
    }

    ComplexNumber operator/(const float& scalar) const {
        if (MathUtils::isNearZero(scalar))
            throw std::runtime_error("Division by zero");
        return ComplexNumber(real_ / scalar, imag_ / scalar);
    }

    // compares complex numbers by checking if they abs difference is < EPS
    bool operator==(const ComplexNumber& other) const {
        return (MathUtils::areEqual(real_, other.real_) &&
                MathUtils::areEqual(imag_, other.imag_));
    }

    bool operator==(const float& other) const {
        return MathUtils::areEqual(real_, other) && MathUtils::isNearZero(imag_);
    }

    bool operator!=(const ComplexNumber& other) const {
        return !(*this == other);
    }

    bool operator!=(const float& other) const {
        return !(*this == other);
    }

    // exp by e^(a + bi) = (e^a)(e^bi) = (e^a)(cosb + isinb)
    ComplexNumber exp() const {
        float e = std::exp(real_);
        return ComplexNumber(e * std::cos(imag_), e * std::sin(imag_));
    }

    // generalizes power by z1^z2 = e^ln(z1^z2) = e^(z2lnz1)
    ComplexNumber operator^(const ComplexNumber& exp) const {
        return (this->ln() * exp).exp();
    }

    // by ln(re^iθ) = ln(r) + ln(e^iθ) = ln(r) + iθ = ln(mod(z)) + iarg(z)
    ComplexNumber ln() const {
        float r = mod();

        if (MathUtils::isNearZero(r))
            throw std::runtime_error("ln(0) undefined");

        return ComplexNumber(std::log(r), arg());
    }

    // by logz2(z1) = logz3(z1) / logz3(z2) = ln(z1) / ln(z2)
    ComplexNumber log(const ComplexNumber& base) const {
        return this->ln() / base.ln();
    }

    // from sin(a+ib) = sinacosib + sinibcosa and cos(ib) = coshb and sinib =
    // isinhb
    ComplexNumber sin() const {
        return ComplexNumber(std::sin(real_) * std::cosh(imag_),
                             std::cos(real_) * std::sinh(imag_));
    }

    // from cos(a+ib) = cosacosib - sinasinib and cosib = coshb and sinib =
    // isinhb
    ComplexNumber cos() const {
        return ComplexNumber(std::cos(real_) * std::cosh(imag_),
                             -std::sin(real_) * std::sinh(imag_));
    }

    // by tanx = sinx/cosx
    ComplexNumber tan() const {
        return sin() / cos();
    }
    // arccos(z) = -i ln(z + sqrt(z^2 - 1))
    // from cos(w) = z, write w = arccos(z)
    // then use the standard inversion identity for cosine:
    // cos(w) = z  <=>  w = -i ln(z + sqrt(z^2 - 1))
    ComplexNumber arccos() const {
        ComplexNumber i(0, 1);
        ComplexNumber one(1, 0);

        return (-i) * ((*this) + ((*this) * (*this) - one).sqrt()).ln();
    }

    // arcsin(z) = -i ln(iz + sqrt(1 - z^2))
    // from sin(w) = z, solve for w using the exponential form of sine
    // sin(w) = (e^{iw} - e^{-iw}) / (2i)
    // which gives w = -i ln(iz + sqrt(1 - z^2))
    ComplexNumber arcsin() const {
        ComplexNumber i(0, 1);
        ComplexNumber one(1, 0);

        return (-i) * (i * (*this) + (one - (*this) * (*this)).sqrt()).ln();
    }

    // arctan(z) = (i/2) ln((1 - iz)/(1 + iz))
    // from tan(w) = z = sin(w)/cos(w)
    // and the exponential forms of sine and cosine
    // this rearranges to w = (i/2) ln((1 - iz)/(1 + iz))
    ComplexNumber arctan() const {
        ComplexNumber i(0, 1);
        ComplexNumber one(1, 0);

        return (i / 2.0) * ((one - i * (*this)) / (one + i * (*this))).ln();
    }

    // sinh(a+ib) = sinh(a)cos(b) + i cosh(a)sin(b)
    // from sinh(x+y) = sinh(x)cosh(y) + cosh(x)sinh(y)
    // with x = a and y = ib
    // and cosh(ib) = cos(b), sinh(ib) = i sin(b)
    ComplexNumber sinh() const {
        return ComplexNumber(std::sinh(real_) * std::cos(imag_),
                             std::cosh(real_) * std::sin(imag_));
    }

    // cosh(a+ib) = cosh(a)cos(b) + i sinh(a)sin(b)
    // from cosh(x+y) = cosh(x)cosh(y) + sinh(x)sinh(y)
    // with x = a and y = ib
    // and cosh(ib) = cos(b), sinh(ib) = i sin(b)
    ComplexNumber cosh() const {
        return ComplexNumber(std::cosh(real_) * std::cos(imag_),
                             std::sinh(real_) * std::sin(imag_));
    }

    // tanh(z) = sinh(z) / cosh(z)
    // same as tan(z) = sin(z) / cos(z), but with hyperbolic functions
    ComplexNumber tanh() const {
        return sinh() / cosh();
    }

    // arccosh(z) = ln(z + sqrt(z^2 - 1))
    // from cosh(w) = z, solve for w
    // using cosh(w) = (e^w + e^{-w})/2
    // which rearranges to w = ln(z + sqrt(z^2 - 1))
    ComplexNumber arccosh() const {
        ComplexNumber one(1, 0);

        return ((*this) + ((*this) * (*this) - one).sqrt()).ln();
    }

    // arcsinh(z) = ln(z + sqrt(z^2 + 1))
    // from sinh(w) = z, solve for w
    // using sinh(w) = (e^w - e^{-w})/2
    // which rearranges to w = ln(z + sqrt(z^2 + 1))
    ComplexNumber arcsinh() const {
        ComplexNumber one(1, 0);
        return ((*this) + ((*this) * (*this) + one).sqrt()).ln();
    }

    // arctanh(z) = (1/2) ln((1 + z)/(1 - z))
    // from tanh(w) = z = (e^w - e^{-w})/(e^w + e^{-w})
    // solve algebraically for e^{2w}
    // getting e^{2w} = (1+z)/(1-z)
    // so w = (1/2)ln((1+z)/(1-z))
    ComplexNumber arctanh() const {
        ComplexNumber one(1, 0);

        return ((one + (*this)) / (one - (*this))).ln() / 2.0;
    }

    std::string printInCartesianForm() const {

        if (MathUtils::isNearZero(imag_))
            return std::to_string(real_);

        else if (imag_ > 0)
            return std::to_string(real_) + " + " + std::to_string(imag_) + "i";

        return std::to_string(real_) + " - " + std::to_string(-imag_) + "i";
    }

    Vector2D toVector2D() const {
        return Vector2D(real_, imag_);
    }

    std::string printInPolarForm() const {
        return std::to_string(mod()) + "e^i" + std::to_string(arg());
    }
};

#endif