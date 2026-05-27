#pragma once

#include "../SymbolicVariable.h"
#include "../nodes/SymbolicNodePair.h"

class SymbolicMultiplication : public SymbolicNodePair {
    
    public :
    SymbolicMultiplication(NodePtr left, NodePtr right) : SymbolicNodePair(std::move(left), std::move(right)) {}

    double evaluate() const override { return left->evaluate() * right->evaluate(); }

     std::string toLatex() const override {
        return "";
    }

    NodePtr simplify() const override {
        return SymbolicNode::makeNode<SymbolicMultiplication>(left, right);
    }

    std::string toString() const override {
          if (dynamic_cast<SymbolicVariable *>(right.get())) {
            return left->toString() + right->toString();
          }
        
        return left->toString() + " * " + right->toString(); }

};