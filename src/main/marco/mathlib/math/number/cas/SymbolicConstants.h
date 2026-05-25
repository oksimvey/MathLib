#ifndef SYMBOLIC_CONSTANTS_H
#define SYMBOLIC_CONSTANTS_H

#include <string>
#include "SymbolicConstant.h"
class SymbolicConstants {

    public:

    constexpr static std::string constants[] = {"e", "π", "ϕ"};

    const inline static SymbolicConstant<float> EulerF = SymbolicConstant<float>(2.718282f, constants[0]);

    const inline static SymbolicConstant<double> EulerD = SymbolicConstant<double>(2.718281828459045,constants[0]);

    const inline static SymbolicConstant<float> PiF = SymbolicConstant<float>(3.141593f, constants[1]);

    const inline static SymbolicConstant<double> PiD = SymbolicConstant<double>(3.141592653589793, constants[1]);

    const inline static SymbolicConstant<float> PhiF = SymbolicConstant<float>(1.618034, constants[2]);

    const inline static SymbolicConstant<double> PhiD = SymbolicConstant<double>(1.6180339887498948, constants[2]);

};

#endif