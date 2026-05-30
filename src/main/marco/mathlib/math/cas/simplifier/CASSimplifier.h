#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include <vector>
class CASSimplifier {

    public:

    static SymbolicNode::NodePtr simplifySum(const std::vector<SymbolicNode::NodePtr>& elements);

    static SymbolicNode::NodePtr simplifyNegative(const SymbolicNode::NodePtr& original);


};