#pragma once

#include "nodes/SymbolicNodePair.h"

class SymbolicSub : public SymbolicNodePair {

public:

    SymbolicSub(NodePtr left, NodePtr right) : SymbolicNodePair(std::move(left), std::move(right)) {}

    double evaluate() override { return left->evaluate() - right->evaluate(); }
    
    std::string toString() override { return left->toString() + " - " + right->toString(); }
};