
#include <cmath>
#include <utility>

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/valued/SymbolicInteger.h"
#include "main/marco/mathlib/math/cas/CASUtils.h"

class SymbolicFraction : public SymbolicNode {

  const NodePtr numerator;
  const NodePtr denominator;

public:

  SymbolicFraction(NodePtr numerator_, NodePtr denominator_)
      : numerator(std::move(numerator_)), denominator(std::move(denominator_)) {
  }

  SymbolicFraction(const SymbolicNode *numerator_,
                   const SymbolicNode *denominator_)
      : numerator(numerator_), denominator(denominator_) {}

  SymbolicFraction(const int &numerator_, const int &denominator_)
      : numerator(makeNode<SymbolicInteger>(numerator_)),
        denominator(makeNode<SymbolicInteger>(denominator_)) {}



        


    static SymbolicNode::NodePtr approximateFraction(
    double x,
    double eps = 1e-8,
    int maxDen = 100000
) {
    if (!std::isfinite(x)) {
        return nullptr;
    }

    bool negative = x < 0;
    double value = std::abs(x);

    int h1 = 1, h0 = 0;
    int k1 = 0, k0 = 1;

    double b = value;

    while (true) {

        int a = (int)std::floor(b);

        int h = a * h1 + h0;
        int k = a * k1 + k0;

        if (k > maxDen) {
            break;
        }

        double approx = (double)h / (double)k;

        if (std::abs(approx - value) <= eps) {
            return makeNode<SymbolicFraction>(
                negative ? -h : h,
                k
            );
        }

        h0 = h1;
        h1 = h;

        k0 = k1;
        k1 = k;

        double frac = b - a;

        if (std::abs(frac) < eps) {
            break;
        }

        b = 1.0 / frac;
    }

    return makeNode<SymbolicFraction>(
        negative ? -h1 : h1,
        k1
    );
}


  [[nodiscard]] NodePtr simplify() const override {
    if (numerator == denominator) {
      return makeNode<SymbolicInteger>(1);
    }
    if (denominator->evaluate() == 1) {
      return numerator->simplify();
    }
    if (CASUtils::areBothNodesOfType<const SymbolicInteger>(numerator, denominator)) {
      int numValue = numerator->evaluate();
      int denValue = denominator->evaluate();

       if (denValue < 0) {
            numValue = -numValue;
            denValue = -denValue;
        }

        int g = std::gcd(std::abs(numValue), std::abs(denValue));

        if (g != 0) {
            numValue /= g;
            denValue /= g;
        }

        return makeNode<SymbolicFraction>(numValue, denValue);

  
    }
    return std::make_shared<SymbolicFraction>(numerator->simplify(),
                                              denominator->simplify());
  }

  [[nodiscard]] NodeType kind() const override { return NodeType::Fraction; }

  [[nodiscard]] std::string toString() const override {
    return numerator->toString() + "/" + denominator->toString();
  };

  [[nodiscard]] std::string toLatexString() const override {
     return "\frac{" + numerator->toLatexString() + "}{" + denominator->toLatexString() + "}"; }  ;

  [[nodiscard]] double evaluate() const override {
    return numerator->evaluate() / denominator->evaluate();
  };
};