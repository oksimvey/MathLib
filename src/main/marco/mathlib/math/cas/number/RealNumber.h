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
#include "main/marco/mathlib/math/cas/nodes/valued/SymbolicNegativeNode.h"
#include "main/marco/mathlib/math/cas/nodes/functions/SymbolicSqrt.h"
#include <memory>

class RealNumber {

  
public:

  SymbolicNode::NodePtr value;

  RealNumber();



  RealNumber(const SymbolicNode::NodePtr& nod):value(nod){};


  RealNumber(const double &real)
     {
        if (real <= 0){
          value =std::make_shared<SymbolicNegativeNode>( SymbolicFraction::approximateFraction(-real)->simplify())->simplify();
        }
        else value = SymbolicFraction::approximateFraction(real)->simplify();
      };

  RealNumber(const int &integer) {
        if (integer <= 0){
          value = std::make_shared<SymbolicNegativeNode>(std::make_shared<SymbolicInteger>(-integer))->simplify();
        }
        else value = std::make_shared<SymbolicInteger>(integer);
      };


  RealNumber operator+(const RealNumber &other) const {
    return RealNumber(SymbolicNode::makeNode<SymbolicSum>(value, other.value)->simplify());
  }

  RealNumber operator-() const {
    return RealNumber(SymbolicNode::makeNode<SymbolicNegativeNode>(value)->simplify());
  }

  RealNumber operator-(const RealNumber &other) const {
    return *this + (RealNumber((-other)));
  }

  RealNumber operator*(const RealNumber &other) const  {
    return RealNumber(value->evaluate() * other.value->evaluate());
  }

  RealNumber operator/(const RealNumber &other) const  {
    return RealNumber(value->evaluate() / other.value->evaluate());
  }

  RealNumber sqrt() const {
    return RealNumber(SymbolicNode::makeNode<SymbolicSqrt>(value));
  }
};


static_assert(Scalar<RealNumber>, "RealNumber is not a Scalar");

