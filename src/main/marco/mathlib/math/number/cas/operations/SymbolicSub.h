#pragma once

#include "../nodes/SymbolicNodePair.h"

class SymbolicSub : public SymbolicNodePair {

public:

    SymbolicSub(NodePtr left_, NodePtr right_) : SymbolicNodePair(std::move(left_), std::move(right_)) {}

    double evaluate() const override { return left->evaluate() - right->evaluate(); }

     std::string toLatex() const override {
        return "";
    }


    
    std::string toString() const override { return left->toString() + " - " + right->toString(); }
};