#ifndef MATHLIB_REALNUMBER_H
#define MATHLIB_REALNUMBER_H

#include "cas/SymbolicFraction.h"
#include "cas/SymbolicInteger.h"
#include "cas/SymbolicSqrt.h"
#include "cas/SymbolicPow.h"
#include "cas/nodes/SymbolicNode.h"
#include "cas/nodes/SymbolicNode.h"
#include "cas/SymbolicSum.h"
#include "cas/SymbolicMultiplication.h"
#include "cas/SymbolicSub.h"

class RealNumber  {


    public :

     NodePtr node;

    RealNumber(NodePtr node) : node(std::move(node)) {}

    RealNumber(int value) : node(makeNode<SymbolicInteger>(value)) {}
    RealNumber operator+(const RealNumber &other) const {
      return RealNumber(makeNode<SymbolicSum>(node, other.node));
    }

    RealNumber &operator+=(const RealNumber &other) {
      *this = *this + other;
      return *this;
    }

    RealNumber operator-(const RealNumber &other)  const {
      return RealNumber(makeNode<SymbolicSub>(node, other.node));
    }

    RealNumber &operator-=(const RealNumber &other) {
      *this = *this - other;
      return *this;
    }

    RealNumber operator*(const RealNumber &other) const {
      return RealNumber(makeNode<SymbolicMultiplication>(node, other.node));
    }

    RealNumber &operator*=(const RealNumber &other) {
      *this = *this * other;
      return *this;
    }

    RealNumber operator/(const RealNumber &other) const {
      return RealNumber(makeNode<SymbolicFraction>(node, other.node));
    }

    RealNumber &operator/=(const RealNumber &other) {
      *this = *this / other;
      return *this;
    }

    RealNumber operator^(const RealNumber &other) const {
      return RealNumber(makeNode<SymbolicPow>(node, other.node));
    }

    RealNumber &operator^=(const RealNumber &other) {
      *this = *this ^ other;
      return *this;
    }

    RealNumber sqrt() const {
      return RealNumber(makeNode<SymbolicSqrt>(node));
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