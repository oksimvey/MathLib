#ifndef SYMBOLIC_POW_H
#define SYMBOLIC_POW_H

#include "../nodes/SymbolicNodePair.h"
#include <cmath>
#include "../utils/CASUtils.h"
#include "../SymbolicNumber.h"
#include "../functions/SymbolicSqrt.h"

class SymbolicPow : public SymbolicNodePair {

    public:

    SymbolicPow(NodePtr left, NodePtr right)
    : SymbolicNodePair(
        std::move(left),
        std::move(right)
      ) {}

       std::string toLatex() const override {
        return "";
    }

    NodePtr simplify()  const override {
        if (CASUtils::isSymbolicNodeOfType<SymbolicNumber>(right)) {
           SymbolicNumber* num = CASUtils::getSymbolicNodeOfType<SymbolicNumber>(right);
           if (num->value == 0){
               return makeNode<SymbolicNumber>(1);
           }
           if (num->value == 1){
             return left;
           }
           if (num-> value == 0.5){
               return SymbolicNode::makeNode<SymbolicSqrt>(left);
           }
        }

        return SymbolicNode::makeNode<SymbolicPow>(left, right);
    }

    std::string toString() const override {
      if (dynamic_cast<SymbolicNodePair *>(right.get())) {
        return   left->toString() + "^" + "(" + right->toString() + ")";
      }
      return left->toString() + "^" + right->toString();
    }

    double evaluate() const override {
        return std::pow(left->evaluate(), right->evaluate());
    }

};

#endif