#ifndef SYMBOLIC_SQRT_H
#define SYMBOLIC_SQRT_H

#include "../nodes/SymbolicNode.h"
#include "../nodes/SymbolicNodePair.h"
#include <cmath>
#include "../utils/CASUtils.h"
#include "../nodes/SymbolicNumber.h"

class SymbolicSqrt : public SymbolicNode {

public:
  NodePtr value;

  SymbolicSqrt(NodePtr value) : value(std::move(value)) {}

  std::string toString() const override {
    return "√" + CASUtils::getStringAsChildren(value);
  }

  std::string toLatex() const override { return ""; }

  double evaluate() const override {
    const double &result = value->evaluate();
    if (result < 0) {
      throw std::runtime_error("Cannot take square root of negative number");
      return 0;
    }
    return std::sqrt(value->evaluate());
  }
};

#endif
