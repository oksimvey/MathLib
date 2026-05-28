#pragma once

#include "SymbolicNode.h"
#include <string>
#include <format>

class SymbolicNumber : public SymbolicNode {

    public:

    const double value;

    SymbolicNumber(double value) : value(value) {}

    std::string toString() const override {
        return std::format("{}", value);
    }

    std::string toLatex() const override {
        return "";
    }


    double evaluate()  const override {
        return value;
    }
};
