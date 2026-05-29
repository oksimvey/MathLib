
#include <utility>

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/valued/SymbolicInteger.h"
#include "main/marco/mathlib/math/cas/utils/CASUtils.h"

class SymbolicFraction : public SymbolicNode {

  const NodePtr numerator;
  const NodePtr denominator;

public:

static SymbolicNode::NodePtr getSimplifiedFraction(const int& n,
                                                   const int& d) {

    if (d == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    int n_ = n;
    int d_ = d;

    // normaliza sinal
    if (d_ < 0) {
        n_ = -n_;
        d_ = -d_;
    }

    int g = std::gcd(std::abs(n_), std::abs(d_));

    int num = n_ / g;
    int den = d_ / g;

    return std::make_shared<SymbolicFraction>(num, den);
}

  static SymbolicNode::NodePtr
getDoubleAsFraction(const double &value) {

    int decimaldigits = CASUtils::countDecimalDigits(value);

    int d = std::pow(10, decimaldigits);

    int n = std::round(value * d);

    return getSimplifiedFraction(n, d);
}

  SymbolicFraction(NodePtr numerator_, NodePtr denominator_)
      : numerator(std::move(numerator_)), denominator(std::move(denominator_)) {
  }

  SymbolicFraction(const SymbolicNode *numerator_,
                   const SymbolicNode *denominator_)
      : numerator(numerator_), denominator(denominator_) {}

  SymbolicFraction(const int &numerator_, const int &denominator_)
      : numerator(makeNode<SymbolicInteger>(numerator_)),
        denominator(makeNode<SymbolicInteger>(denominator_)) {}



  [[nodiscard]] NodePtr simplify() const override {
    if (numerator == denominator) {
      return makeNode<SymbolicInteger>(1);
    }
    if (denominator->evaluate() == 1) {
      return numerator->simplify();
    }
    if (CASUtils::areBothNodesOfType<const SymbolicInteger>(numerator, denominator)) {

      
      return 
      getSimplifiedFraction(numerator->evaluate(),
                                             denominator->evaluate());
    }
    return std::make_shared<SymbolicFraction>(numerator->simplify(),
                                              denominator->simplify());
  }

  [[nodiscard]] NodeType kind() const override { return NodeType::Fraction; }

  [[nodiscard]] std::string toString() const override {
    return numerator->toString() + " / " + denominator->toString();
  };

  [[nodiscard]] std::string toLatexString() const override { return ""; };

  [[nodiscard]] double evaluate() const override {
    return numerator->evaluate() / denominator->evaluate();
  };
};