#pragma once

#include <unordered_map>

#include "main/marco/mathlib/math/number/scalar/ComplexNumber.h"
#include "nodes/SymbolicNode.h"

class SymbolicVariable : public SymbolicNode {

std::string name;

     std::unordered_map<std::string, double>* variables;

public:

    SymbolicVariable(std::string name, std::unordered_map<std::string, double>* vars) : name(name), variables(vars) {}


    void setValue(const double& value) const {
        (*variables)[name] = value;
    }

    std::string toString() const override {
        return name;
    }

    std::string toLatex() const override { return ""; }

    NodePtr simplify() const override {
        return makeNode<SymbolicVariable>(name, variables&);
    }

    double evaluateVariable(const double& value){
        return value;
    } 

    double evaluate() const override {
        if (variables->contains(name)) {
            return variables->at(name);
        }
        throw std::runtime_error("Cannot evaluate variable");
        return 0;
    }
};