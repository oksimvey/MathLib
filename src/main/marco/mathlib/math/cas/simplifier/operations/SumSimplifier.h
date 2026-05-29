#pragma once


#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/operations/SymbolicSum.h"
#include "main/marco/mathlib/math/cas/CASUtils.h"
#include <vector>

class SumSimplifier {



    static std::vector<SymbolicNode::NodePtr> aclopateSumNodes(const std::vector<SymbolicNode::NodePtr>& elements){
        std::vector<SymbolicNode::NodePtr> toReturn;

        for (const SymbolicNode::NodePtr& element : elements){
            if (element->kind() == NodeType::Addition) {
                
            }
        }

        return toReturn;
    }


    public:

    static SymbolicNode::NodePtr simplify(const std::vector<SymbolicNode::NodePtr>& elements) {
        std::vector<SymbolicNode::NodePtr> accloped = aclopateSumNodes(elements);
    }

};