#pragma once

#include "../nodes/SymbolicNodePair.h"

class SymbolicSub : public SymbolicNodePair {

public:

    SymbolicSub(NodePtr left, NodePtr right) : SymbolicNodePair(std::move(left), std::move(right)) {}

    double evaluate() const override { return left->evaluate() - right->evaluate(); }

     std::string toLatex() const override {
        return "";
    }

    NodePtr simplify() const override {
        return SymbolicNode::makeNode<SymbolicSub>(left, right);
    }
    
    std::string toString() const override { return left->toString() + " - " + right->toString(); }
};