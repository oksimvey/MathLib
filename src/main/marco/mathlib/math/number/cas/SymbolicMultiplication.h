#pragma once

#include "nodes/SymbolicNodePair.h"

class SymbolicMultiplication : public SymbolicNodePair {
    
    public :
    SymbolicMultiplication(NodePtr left, NodePtr right) : SymbolicNodePair(std::move(left), std::move(right)) {}

    double evaluate() override { return left->evaluate() * right->evaluate(); }

    std::string toString() override { return left->toString() + " * " + right->toString(); }

};