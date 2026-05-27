#pragma once

#include "nodes/SymbolicNode.h"

class SymbolicVariable : public SymbolicNode {

std::string name;

public:

    SymbolicVariable(std::string name) : name(name) {}

    std::string toString() const override {
        return name;
    }

    std::string toLatex() const override { return ""; }

    NodePtr simplify() const override {
        return makeNode<SymbolicVariable>(name);
    }

    double evaluateVariable(const double& value){
        return value;
    } 

    double evaluate() const override {
        throw std::runtime_error("Cannot evaluate variable");
        return 0;
    }
};