#pragma once

#include "nodes/SymbolicNode.h"
#include <string>
#include <format>

class SymbolicNumber : public SymbolicNode {

    public:

    const double value;

    SymbolicNumber(double value) : value(value) {   }



    std::string toString() const override {
        return std::format("{}", value);
    }

    std::string toLatex() const override {
        return "";
    }

    NodePtr simplify()  const override {
        return makeNode<SymbolicNumber>(value);
    }

    double evaluate()  const override {
        return value;
    }
};
