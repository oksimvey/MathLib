#ifndef SYMBOLICPOW_H
#define SYMBOLICPOW_H

#include <cmath>
#include <string>
#include <sstream>
template<typename T>
class SymbolicPow {

    const T base;

    const T exponent;

    public:

    static_assert(std::is_arithmetic<T>::value, "SymbolicPow requires an arithmetic type");

        SymbolicPow(T base, T exponent) : base(base), exponent(exponent) {}

        SymbolicPow(const std::string& str) : base(std::stod(str.substr(0, str.find('^')))), exponent(std::stod(str.substr(str.find('^') + 1))) {}

    std::string toString() const {
    std::ostringstream oss;
    oss << base << "^" << exponent;
    return oss.str();
}

    T evaluate() const {
        return std::pow(base, exponent);
    }



};


#endif