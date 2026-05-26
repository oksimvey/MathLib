#ifndef SYMBOLIC_POW_H
#define SYMBOLIC_POW_H

#include "nodes/SymbolicNodePair.h"
#include <cmath>

class SymbolicPow : public SymbolicNodePair {

    public:

    SymbolicPow(NodePtr left, NodePtr right)
    : SymbolicNodePair(
        std::move(left),
        std::move(right)
      ) {}

    std::string toString() override {
      if (dynamic_cast<SymbolicNodePair *>(right.get())) {
        return   left->toString() + "^" + "(" + right->toString() + ")";
      }
      return left->toString() + "^" + right->toString();
    }

    double evaluate() override {
        return std::pow(left->evaluate(), right->evaluate());
    }

};

#endif