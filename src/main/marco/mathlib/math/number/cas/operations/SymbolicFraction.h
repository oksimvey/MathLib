#ifndef SYMBOLIC_FRACTION_H
#define SYMBOLIC_FRACTION_H

#include "../nodes/SymbolicNodePair.h"
#include <memory>
#include <string>

class SymbolicFraction : public SymbolicNodePair {

public:
  SymbolicFraction(NodePtr left, NodePtr right)
      : SymbolicNodePair(std::move(left), std::move(right)) {}

  std::string centerText(const std::string &text, size_t width)const {
    size_t padding = (width - text.size()) / 2;

    return std::string(padding, ' ') + text;
  }

    std::string toLatex() const override {
        return "";
    }

    NodePtr simplify() const override {
        return SymbolicNode::makeNode<SymbolicFraction>(left, right);
    }

  double evaluate() const override { return left->evaluate() / right->evaluate(); }

  std::string toString() const override {
    const std::string &numerator = left->toString();
    const std::string &denominator = right->toString();
    size_t width = std::max(numerator.size(), denominator.size());

    std::string line;

    for (size_t i = 0; i < width; i++) {
      line += "─";
    }

    std::string result;
  

    result += centerText(numerator, width);
    result += '\n';

    result += line + " = " + std::to_string(evaluate());
    result += '\n';

    result += centerText(denominator, width);

    return result;
  }
};

#endif