//
// Created by hapoe on 5/27/2026.
//

#ifndef MATHLIB_EXPRESSIONSIMPLIFIER_H
#define MATHLIB_EXPRESSIONSIMPLIFIER_H
#include <memory>

#include "main/marco/mathlib/math/number/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/number/cas/nodes/SymbolicNumber.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicFraction.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicSub.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicSum.h"
#include "main/marco/mathlib/math/number/cas/utils/CASUtils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <numeric>

class ExpressionSimplifier {

    public:




    static SymbolicNode::NodePtr simplifySum(const SymbolicNode::NodePtr& left, const SymbolicNode::NodePtr& right) {
        if (CASUtils::areBothNodesOfType<SymbolicNumber>(left, right)) {
            return SymbolicNode::makeNode<SymbolicNumber>(left->evaluate() + right->evaluate());
        }
        SymbolicNode::NodePtr result = SymbolicNode::makeNode<SymbolicSum>(left, right);
        if (CASUtils::areBothNodesOfType<SymbolicFraction>(left, right)) {
            auto* fraction1 = CASUtils::getSymbolicNodeOfType<SymbolicFraction>(left);
            auto* fraction2 = CASUtils::getSymbolicNodeOfType<SymbolicFraction>(right);

            return SymbolicNode::makeNode<SymbolicFraction>(

            SymbolicNode::makeNode<SymbolicSum>(
                SymbolicNode::makeNode<SymbolicNumber>(fraction1->right->evaluate() * fraction2->left->evaluate()),
                SymbolicNode::makeNode<SymbolicNumber>(fraction1->left->evaluate() * fraction2->right->evaluate())

                    ), SymbolicNode::makeNode<SymbolicNumber>(fraction1->right->evaluate() * fraction2->right->evaluate())
                );
        }



        if (right->evaluate() < 0) {
            result = SymbolicNode::makeNode<SymbolicSub>(left, right);
        }
        return result;
    }

    static SymbolicNode::NodePtr simplifySub(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return nullptr;
    }

    static SymbolicNode::NodePtr simplifyMul(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return nullptr;
    }

    static SymbolicNode::NodePtr simplifyFrac(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        int num = CASUtils::getSymbolicNodeOfType<SymbolicNumber>(node1)->evaluate();
        int den = CASUtils::getSymbolicNodeOfType<SymbolicNumber>(node2)->evaluate();
        int g = std::gcd(num, den);

        num /= g;
        den /= g;

        // deixa o sinal só no numerador
        if (den < 0) {
            den = -den;
            num = -num;
        }
        return SymbolicNode::makeNode<SymbolicFraction>(
            SymbolicNode::makeNode<SymbolicNumber>(num),
            SymbolicNode::makeNode<SymbolicNumber>(den) );
    }

    static int decimalPlaces(const double& x) {
        std::stringstream ss;

        ss << std::fixed << std::setprecision(15) << x;

        std::string s = ss.str();

        while (!s.empty() && s.back() == '0')
            s.pop_back();

        if (!s.empty() && s.back() == '.')
            return 0;

        auto pos = s.find('.');

        if (pos == std::string::npos)
            return 0;

        return s.size() - pos - 1;
    }

    static SymbolicNode::NodePtr toFraction(const double& value) {
        int amount = decimalPlaces(value);
        int divisor = std::pow(10.0, amount);
        int numerator = value * divisor;
        return simplifyFrac(SymbolicNode::makeNode<SymbolicNumber>(numerator), SymbolicNode::makeNode<SymbolicNumber>(divisor));
    }

    static SymbolicNode::NodePtr simplifyPow(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return nullptr;
    }

    static SymbolicNode::NodePtr simplifyLog(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return nullptr;
    }



};

#endif //MATHLIB_EXPRESSIONSIMPLIFIER_H
