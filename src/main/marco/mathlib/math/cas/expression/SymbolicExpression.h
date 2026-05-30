#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/operations/SymbolicSum.h"
#include "main/marco/mathlib/math/cas/nodes/valued/SymbolicVariable.h"
#include <string>
#include <unordered_map>
template <typename T> class SymbolicExpression {

  const std::unordered_map<std::string, SymbolicVariable<T>> varManager;

  const SymbolicNode::NodePtr node;

public:

  SymbolicExpression(const SymbolicNode::NodePtr &node, const std::unordered_map<std::string, SymbolicVariable<T>> vman) : node(node), varManager(vman) {

  }


  void putVariable(const std::string &var, const T &value) {
    varManager[var] = value;
  }

  T getVariable(const std::string &var) { return varManager[var]; }

  SymbolicExpression<T> operator+(const T& element) const {

  }

  SymbolicExpression<T> operator+(const std::string &element) const {
    
    SymbolicVariable<T> var;
    if(varManager.contains(element)){
      var = varManager[element];
    }

    else var = SymbolicNode::makeNode<SymbolicVariable<T>>();

     return SymbolicExpression<T>(
      SymbolicNode::makeNode<SymbolicSum>(node, var), varManager);
  
  }

};