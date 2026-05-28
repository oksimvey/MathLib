#pragma once

#include "SymbolicSum.h"
#include "../utils/CASUtils.h"
#include "../nodes/SymbolicNodePair.h"

class SymbolicMultiplication : public SymbolicNodePair {
    
    public :
    SymbolicMultiplication(NodePtr left_, NodePtr right_) : SymbolicNodePair(std::move(left_), std::move(right_)) {}

    double evaluate() const override { return left->evaluate() * right->evaluate(); }

     std::string toLatex() const override {
        return "";
    }

    std::string toString() const override {
        
        return CASUtils::getAsChildrenIfType<SymbolicSum>(left) + " * " + CASUtils::getAsChildrenIfType<SymbolicSum>(right); }

};