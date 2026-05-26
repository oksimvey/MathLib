#ifndef SYMBOLIC_SQRT_H
#define SYMBOLIC_SQRT_H

#include "nodes/SymbolicNode.h"
#include <cmath>
#include "nodes/SymbolicNodePair.h"

class SymbolicSqrt: public SymbolicNode {

    public:

        NodePtr value;

        SymbolicSqrt(NodePtr value) : value(std::move(value)) {}

        std::string toString() override {
          if (dynamic_cast<SymbolicNodePair *>(value.get())) {
            return "√(" + value->toString() + ")";
          }
          return "√" + value->toString();
        }

        double evaluate() override {
            return std::sqrt(value->evaluate());
        }



};

#endif
