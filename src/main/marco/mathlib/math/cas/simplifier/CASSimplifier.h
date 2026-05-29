#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/simplifier/operations/SumSimplifier.h"
#include "operations/SumSimplifier.h"
#include <vector>
class CASSimplifier {

    public:

    static SymbolicNode::NodePtr simplifySum(const std::vector<SymbolicNode::NodePtr>& elements){
        return SumSimplifier::simplify(elements);
    }


};