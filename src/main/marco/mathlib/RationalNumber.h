#ifndef RATIONAL_NUMBER_H
#define RATIONAL_NUMBER_H

class RationalNumber {

public:

    RationalNumber(const int& numerator, const int& denominator);
    RationalNumber(const int& numerator);
    RationalNumber();
    RationalNumber operator+(const RationalNumber& other) const;
    RationalNumber operator-(const RationalNumber& other) const;
    RationalNumber operator*(const RationalNumber& other) const;
    RationalNumber operator/(const RationalNumber& other) const;
    bool operator==(const RationalNumber& other) const;
    bool operator!=(const RationalNumber& other) const;
    void print() const;
    RationalNumber simplify() const;

private:
    const int numerator_;
    const int denominator_;
};

#endif // RATIONAL_NUMBER_H