//
// Created by hapoe on 5/27/2026.
//

#ifndef MATHLIB_NUMERICEXPRESSIONPARSER_H
#define MATHLIB_NUMERICEXPRESSIONPARSER_H
#include <string>
#include <unordered_map>

#include "main/marco/mathlib/math/number/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicFraction.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicMultiplication.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicPow.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicSub.h"
#include "main/marco/mathlib/math/number/cas/operations/SymbolicSum.h"

class NumericExpressionParser {

public:

    static std::unordered_map<std::string, SymbolicNode::NodePtr(*)(const SymbolicNode::NodePtr&, const SymbolicNode::NodePtr&)> operations;

    static SymbolicNode::NodePtr operationSum(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return SymbolicNode::makeNode<SymbolicSum>(node1, node2);
    }

    static SymbolicNode::NodePtr operationSub(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return SymbolicNode::makeNode<SymbolicSub>(node1, node2);
    }

    static SymbolicNode::NodePtr operationMul(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return SymbolicNode::makeNode<SymbolicMultiplication>(node1, node2);
    }

    static SymbolicNode::NodePtr operationDiv(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return SymbolicNode::makeNode<SymbolicFraction>(node1, node2);
    }

    static SymbolicNode::NodePtr operationPow(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return SymbolicNode::makeNode<SymbolicPow>(node1, node2);
    }

    static void initOperations() {
        operations["+"] = operationSum;
        operations["-"] = operationSub;
        operations["*"] = operationMul;
        operations["/"] = operationDiv;
        operations["^"] = operationPow;
    }


};

#endif //MATHLIB_NUMERICEXPRESSIONPARSER_H
