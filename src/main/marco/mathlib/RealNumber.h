#ifndef MATHLIB_REALNUMBER_H
#define MATHLIB_REALNUMBER_H

#include <iostream>
#include <cmath>
#include <cstdint>
#include <string>
#include <algorithm>
#include "Scalar.h"

class RealNumber : public Scalar {

    public:

        const __int128 value;

        const uint8_t decimals;

        RealNumber(__int128 value, uint8_t decimals) : value(value), decimals(decimals) {}


        RealNumber(const double& number) : value(static_cast<__int128>(number * pow(10, 10))), decimals(10) {}

        bool operator==(const RealNumber& other) const {
            if (decimals == other.decimals) {
                return value == other.value;
            } 
            else if (decimals > other.decimals) {
                __int128 scaledValue = other.value * pow(10, decimals - other.decimals);
                return value == scaledValue;
            } 
            else {
                __int128 scaledValue = value * pow(10, other.decimals - decimals);
                return scaledValue == other.value;
            }
        }

    
    

        RealNumber operator+(const RealNumber& other) const {
            if (decimals == other.decimals) {
                return RealNumber(value + other.value, decimals);
            } 
            else if (decimals > other.decimals) {
                __int128 scaledValue = other.value * pow(10, decimals - other.decimals);
                return RealNumber(value + scaledValue, decimals);
            } 
            else {
                __int128 scaledValue = value * pow(10, other.decimals - decimals);
                return RealNumber(scaledValue + other.value, other.decimals);
            }
        }

        std::string int128ToString(__int128 value) const {

    if (value == 0)
        return "0";

    bool negative = value < 0;

    if (negative)
        value = -value;

    std::string str;

    while (value > 0) {
        str += '0' + value % 10;
        value /= 10;
    }

    if (negative)
        str += '-';

    std::reverse(str.begin(), str.end());

    return str;
}

        

        std::string toString() const {
        std::string strValue = int128ToString(value);

    if (decimals > 0) {

        if (strValue.length() <= decimals) {
            strValue.insert(0, decimals - strValue.length() + 1, '0');
        }

        strValue.insert(strValue.end() - decimals, '.');
    }

    return strValue;
        }






};

#endif // MATHLIB_REALNUMBER_H