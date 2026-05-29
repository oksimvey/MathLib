//
// Created by hapoe on 5/28/2026.
//

#pragma once
#include "Scalar.h"
#include "main/marco/mathlib/math/cas/nodes/NodeType.h"
#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/operations/SymbolicSum.h"
#include "main/marco/mathlib/math/cas/nodes/valued/SymbolicInteger.h"
#include "main/marco/mathlib/math/cas/nodes/operations/SymbolicFraction.h"

class RealNumber {

  
public:

  SymbolicNode::NodePtr value;

  RealNumber();

  

  RealNumber(const SymbolicNode::NodePtr& nod):value(nod){};


  RealNumber(const double &real)
      : value(SymbolicFraction::approximateFraction(real)->simplify()) {};

  RealNumber(const int &integer)
      : value(std::make_shared<SymbolicInteger>(integer)->simplify()) {};


  RealNumber operator+(const RealNumber &other) const {
    return RealNumber(SymbolicNode::makeNode<SymbolicSum>(value, other.value));
  }

  RealNumber operator-(const RealNumber &other) const {
    return RealNumber(value->evaluate() - other.value->evaluate());
  }

  RealNumber operator*(const RealNumber &other) const  {
    return RealNumber(value->evaluate() * other.value->evaluate());
  }

  RealNumber operator/(const RealNumber &other) const  {
    return RealNumber(value->evaluate() / other.value->evaluate());
  }
};


static_assert(Scalar<RealNumber>, "RealNumber is not a Scalar");

