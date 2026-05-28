//
// Created by hapoe on 5/27/2026.
//

#ifndef MATHLIB_SYMBOLICEXPRESSION_H
#define MATHLIB_SYMBOLICEXPRESSION_H
#include <string>
#include <unordered_map>
#include "../../scalar/ComplexNumber.h"

class SymbolicExpression {


public:

    std::unordered_map<std::string, ComplexNumber> variables;

};

#endif //MATHLIB_SYMBOLICEXPRESSION_H
