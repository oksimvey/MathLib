#pragma once

#include "main/marco/mathlib/math/cas/CASUtils.h"
#include "main/marco/mathlib/math/cas/nodes/NodeType.h"
#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/simplifier/CASSimplifier.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
class SymbolicNegativeNode : public SymbolicNode {


     SymbolicNode::NodePtr original;

    public:

    SymbolicNode::NodePtr getOriginal() const{
        return original;
    }

    SymbolicNegativeNode(const SymbolicNode::NodePtr& node) : original(node){};

    [[nodiscard]] std::string toString() const override {
      if (CASUtils::isMultipleNode(original)) {
        return "-(" + original->toString() + ")";
      }

      return "-" + original->toString();
    }

    [[nodiscard]] double evaluate() const override {
        return -original->evaluate();
    }

      [[nodiscard]] std::string toLatexString() const override {
        return "";
    };

    [[nodiscard]] NodeType kind() const override {
        return NodeType::Negative;
    }

   
[[nodiscard]] SymbolicNode::NodePtr simplify() const override {
    return CASSimplifier::simplifyNegative(original);
}



};