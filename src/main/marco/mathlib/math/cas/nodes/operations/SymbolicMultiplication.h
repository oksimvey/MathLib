#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include <vector>
class SymbolicMultiplication : public SymbolicNode {

    std::vector<SymbolicNode::NodePtr> nodes;

    public: 

    SymbolicMultiplication(const std::vector<SymbolicNode::NodePtr>& nodes) : nodes(nodes) {};







};