#pragma once

#include "../SymbolicNumber.h"
#include "SymbolicMultiplication.h"
#include "../SymbolicVariable.h"
#include "../nodes/SymbolicNodePair.h"
#include <algorithm>

class SymbolicSum : public SymbolicNodePair {
public:

    SymbolicSum(NodePtr left, NodePtr right) : SymbolicNodePair(std::move(left),std::move(right)) {}

    double evaluate() const override { return left->evaluate() + right->evaluate(); }

     std::string toLatex() const override {
        return "";
    }

     NodePtr simplify() const override {
    auto* leftMul  = dynamic_cast<SymbolicMultiplication*>(left.get());
    auto* rightMul = dynamic_cast<SymbolicMultiplication*>(right.get());

    auto extractCoeffAndVar = [](SymbolicMultiplication* mul,
                                 SymbolicNumber*& coeff,
                                 SymbolicVariable*& var) -> bool {
        if (!mul) return false;

        // caso padrão: Int * Var
        coeff = dynamic_cast<SymbolicNumber*>(mul->left.get());
        var   = dynamic_cast<SymbolicVariable*>(mul->right.get());
        if (coeff && var) return true;

        return false;
    };

    SymbolicNumber* leftCoeff = nullptr;
    SymbolicVariable* leftVar = nullptr;
    SymbolicNumber* rightCoeff = nullptr;
    SymbolicVariable* rightVar = nullptr;

    if (extractCoeffAndVar(leftMul, leftCoeff, leftVar) &&
        extractCoeffAndVar(rightMul, rightCoeff, rightVar) &&
        leftVar->toString() == rightVar->toString()) {

        return SymbolicNode::makeNode<SymbolicMultiplication>(
            SymbolicNode::makeNode<SymbolicNumber>(leftCoeff->value + rightCoeff->value),
            SymbolicNode::makeNode<SymbolicVariable>(leftVar->toString())
        );
    }

    return SymbolicNode::makeNode<SymbolicSum>(left, right);
}

    std::string toString() const override { return left->toString() + " + " + right->toString(); }


};

