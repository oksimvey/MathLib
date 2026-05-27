#ifndef SYMBOLIC_SQRT_H
#define SYMBOLIC_SQRT_H

#include "../nodes/SymbolicNode.h"
#include "../nodes/SymbolicNodePair.h"
#include <cmath>
#include "../utils/CASUtils.h"
#include "../SymbolicNumber.h"

class SymbolicSqrt : public SymbolicNode {

public:
  NodePtr value;

  SymbolicSqrt(NodePtr value) : value(std::move(value)) {}

  std::string toString() const override {
    return "√" + CASUtils::getStringAsChildren(value);
  }

  std::string toLatex() const override { return ""; }

 NodePtr simplify() const override {

   // if (CASUtils::isSymbolicNodeOfType<SymbolicPow>(value)) {

   //     auto pow = CASUtils::getSymbolicNodeOfType<SymbolicPow>(value);

   //     NodePtr exponent = pow->right;

    //    if (CASUtils::isSymbolicNodeOfType<SymbolicNumber>(exponent)) {

     //       auto num = CASUtils::getSymbolicNodeOfType<SymbolicNumber>(exponent);

      //      double v = num->value;

            // checa se é inteiro
     //       if (std::floor(v) == v) {

         //       int n = static_cast<int>(v);

                // expoente par
        //        if (n % 2 == 0) {

          //          return makeNode<SymbolicPow>(
          //              pow->left,
           //             makeNode<SymbolicNumber>(n / 2)
           //         );

          //      }
         //   }
      //  }
   // }

    return makeNode<SymbolicSqrt>(value);
}

  double evaluate() const override {
    const double &result = value->evaluate();
    if (result < 0) {
      throw std::runtime_error("Cannot take square root of negative number");
      return 0;
    }
    return std::sqrt(value->evaluate());
  }
};

#endif
