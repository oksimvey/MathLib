#include "RationalNumber.h"
#include <iostream>

RationalNumber::RationalNumber(const int& numerator, const int& denominator) : numerator_(numerator), denominator_(denominator) {}

RationalNumber::RationalNumber(const int& numerator) : numerator_(numerator), denominator_(1) {}

RationalNumber::RationalNumber() : numerator_(0), denominator_(1) {}

RationalNumber RationalNumber::operator+(const RationalNumber& other) const {
    int new_numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    int new_denominator = denominator_ * other.denominator_;
    return RationalNumber(new_numerator, new_denominator).simplify();
}

RationalNumber RationalNumber::operator-(const RationalNumber& other) const {
    int new_numerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
    int new_denominator = denominator_ * other.denominator_;
    return RationalNumber(new_numerator, new_denominator).simplify();
}

RationalNumber RationalNumber::operator*(const RationalNumber& other) const {
    int new_numerator = numerator_ * other.numerator_;
    int new_denominator = denominator_ * other.denominator_;
    return RationalNumber(new_numerator, new_denominator).simplify();
}

RationalNumber RationalNumber::operator/(const RationalNumber& other) const {
    int new_numerator = numerator_ * other.denominator_;
    int new_denominator = denominator_ * other.numerator_;
    return RationalNumber(new_numerator, new_denominator).simplify();
}

bool RationalNumber::operator==(const RationalNumber& other) const {
    return numerator_ * other.denominator_ == other.numerator_ * denominator_;
}

bool RationalNumber::operator!=(const RationalNumber& other) const {
    return !(*this == other);
}

void RationalNumber::print() const {
    if (denominator_ == 1) {
        std::cout << numerator_ << std::endl;
    } 
    else {
        std::cout << numerator_ << "/" << denominator_ << std::endl;
    }
}

RationalNumber RationalNumber::simplify() const {
    int gcd = 1;
    int min_value = std::min(numerator_, denominator_);
    for (int i = 2; i <= min_value; ++i) {
        if (numerator_ % i == 0 && denominator_ % i == 0) {
            gcd = i;
        }
    }
    return RationalNumber(numerator_ / gcd, denominator_ / gcd);
}

