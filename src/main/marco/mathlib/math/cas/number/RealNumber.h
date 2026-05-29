//
// Created by hapoe on 5/28/2026.
//

#pragma once
#include "Scalar.h"
#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/valued/SymbolicInteger.h"
#include "main/marco/mathlib/math/cas/utils/CASUtils.h"
#include "main/marco/mathlib/math/cas/nodes/operations/SymbolicFraction.h"

class RealNumber : public Scalar<RealNumber> {

public:
  SymbolicNode::NodePtr value;

  RealNumber();



  RealNumber(const double &real)
      : value(SymbolicFraction::getDoubleAsFraction(real)->simplify()) {};

  RealNumber(const int &integer)
      : value(std::make_shared<SymbolicInteger>(integer)->simplify()) {};


  RealNumber operator+(const RealNumber &other) const override {
    return RealNumber(value->evaluate() + other.value->evaluate());
  }

  RealNumber operator-(const RealNumber &other) const override {
    return RealNumber(value->evaluate() - other.value->evaluate());
  }

  RealNumber operator*(const RealNumber &other) const override {
    return RealNumber(value->evaluate() * other.value->evaluate());
  }

  RealNumber operator/(const RealNumber &other) const override {
    return RealNumber(value->evaluate() / other.value->evaluate());
  }
};
