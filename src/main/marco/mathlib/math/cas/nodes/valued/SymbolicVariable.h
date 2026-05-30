#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include <unordered_map>
#include <vector>

template<typename T>
class SymbolicVariable : public SymbolicNode {

    std::string var;

    T varValue;

    public:

    void setValue(const T& value){(*varValue)[var] = value;}

    T getValue(){return (*varValue)[var];}

     [[nodiscard]] NodeType kind() const override { return NodeType::Variable; }

  [[nodiscard]] std::string toString() const override {
    return var;
  };

  [[nodiscard]] std::string toLatexString() const override { return ""; };

  [[nodiscard]] double evaluate() const override {
    return 0;
  };



};