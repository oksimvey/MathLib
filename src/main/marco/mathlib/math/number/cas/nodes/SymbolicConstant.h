#pragma once


#include "SymbolicNode.h"
#include <string>
#include <format>

class SymbolicConstant : public SymbolicNode {

public:

    const std::string symbol;

    const double value;

    SymbolicConstant(std::string symbol, double value) : symbol(symbol), value(value) {}

    std::string toString() const override {
        return symbol;
    }

    std::string toLatex() const override {
        return "";
    }

    NodePtr simplify()  const override {
        return makeNode<SymbolicConstant>(symbol, value);
    }

    double evaluate()  const override {
        return value;
    }
};
