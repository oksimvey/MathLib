#include "CASSimplifier.h"
#include "functions/NegativeSimplifier.h"
#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "operations/SumSimplifier.h"

SymbolicNode::NodePtr CASSimplifier::simplifySum(const std::vector<SymbolicNode::NodePtr> &elements){
    return SumSimplifier::simplify(elements);
}

SymbolicNode::NodePtr CASSimplifier::simplifyNegative(const SymbolicNode::NodePtr &original){
    return NegativeSimplifier::simplify(original);

}