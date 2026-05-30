#pragma once

#include "main/marco/mathlib/math/cas/CASUtils.h"
#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include <cmath>

class SymbolicSqrt : public SymbolicNode {

  SymbolicNode::NodePtr node;

public:
  SymbolicSqrt(const SymbolicNode::NodePtr &node) : node(node) {}

  [[nodiscard]] NodePtr simplify() const override {
      return makeNode<SymbolicSqrt>(node);
  }

  [[nodiscard]] NodeType kind() const override { return NodeType::Sqrt; }

  [[nodiscard]] std::string toString() const override {
    return "√" + CASUtils::getWithParenthesisIfMultiple(node);
  };
  [[nodiscard]] std::string toLatexString() const override { return ""; };

  [[nodiscard]] double evaluate() const override {
    return std::sqrt(node->evaluate());
  };
};