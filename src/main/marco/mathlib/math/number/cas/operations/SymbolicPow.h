#ifndef SYMBOLIC_POW_H
#define SYMBOLIC_POW_H

#include "../nodes/SymbolicNodePair.h"
#include <cmath>
#include "../utils/CASUtils.h"
#include "../nodes/SymbolicNumber.h"
#include "../functions/SymbolicSqrt.h"

class SymbolicPow : public SymbolicNodePair {

    public:

    SymbolicPow(NodePtr left_, NodePtr right_)
    : SymbolicNodePair(
        std::move(left_),
        std::move(right_)
      ) {}

       std::string toLatex() const override {
        return "";
    }


    std::string toString() const override {
      if (dynamic_cast<SymbolicNodePair *>(right.get())) {
        return   left->toString() + "^" + "(" + right->toString() + ")";
      }
      return left->toString() + "^" + right->toString();
    }

    double evaluate() const override {
        return std::pow(left->evaluate(), right->evaluate());
    }

};

#endif