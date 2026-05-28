#ifndef MATHLIB_REALNUMBER_H
#define MATHLIB_REALNUMBER_H

#include "../cas/nodes/SymbolicNumber.h"
#include "../cas/operations/SymbolicFraction.h"
#include "../cas/functions/SymbolicSqrt.h"
#include "../cas/operations/SymbolicPow.h"
#include "../cas/nodes/SymbolicVariable.h"
#include "../cas/nodes/SymbolicNode.h"
#include "../cas/operations/SymbolicSum.h"
#include "../cas/operations/SymbolicMultiplication.h"
#include "../cas/operations/SymbolicSub.h"
#include "../cas/simplifier/ExpressionSimplifier.h"
#include <string>

class RealNumber  {


    public :

     SymbolicNode::NodePtr node;

     std::string toString() const { return node->toString(); }

     double evaluate() const { return node->evaluate(); }

    RealNumber(SymbolicNode::NodePtr node_) : node(std::move(node_)) {}

    RealNumber(double value) {
       node = ExpressionSimplifier::toFraction(value);
     }

    RealNumber operator+(const RealNumber &other) const {
      return {ExpressionSimplifier::simplifySum(node, other.node)};
    }

    RealNumber &operator+=(const RealNumber &other) {
      *this = *this + other;
      return *this;
    }

    RealNumber operator-(const RealNumber &other)  const {
       return {ExpressionSimplifier::simplifySub(node, other.node)};
    }

    RealNumber &operator-=(const RealNumber &other) {
      *this = *this - other;
      return *this;
    }

    RealNumber operator*(const RealNumber &other) const {
       return {ExpressionSimplifier::simplifyMul(node, other.node)};
    }

    RealNumber &operator*=(const RealNumber &other) {
      *this = *this * other;
      return *this;
    }

    RealNumber operator/(const RealNumber &other) const {
       return {ExpressionSimplifier::simplifyFrac(node, other.node)};
    }

    RealNumber &operator/=(const RealNumber &other) {
      *this = *this / other;
      return *this;
    }

    RealNumber operator^(const RealNumber &other) const {
       return {ExpressionSimplifier::simplifySum(node, other.node)};
    }

    RealNumber &operator^=(const RealNumber &other) {
      *this = *this ^ other;
      return *this;
    }

    RealNumber sqrt() const {
      return RealNumber(SymbolicNode::makeNode<SymbolicSqrt>(node));
    }

    RealNumber exp() const;

    RealNumber ln() const;

    RealNumber log(RealNumber base) const;

    RealNumber cos() const;

    RealNumber sin() const;

    RealNumber tan() const;

    RealNumber abs() const;

    RealNumber acos() const;

    RealNumber asin() const;

    RealNumber atan() const;

    RealNumber atan2(RealNumber y, RealNumber x) const;

    RealNumber cosh() const;

    RealNumber sinh() const;

    RealNumber tanh() const;

    RealNumber acosh() const;

    RealNumber asinh() const;

    RealNumber atanh() const;

};

#endif // MATHLIB_REALNUMBER_H