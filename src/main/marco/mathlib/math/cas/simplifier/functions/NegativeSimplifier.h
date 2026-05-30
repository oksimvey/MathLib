#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/operations/SymbolicSum.h"
#include "main/marco/mathlib/math/cas/nodes/valued/SymbolicNegativeNode.h"
class NegativeSimplifier {

    public:

    static SymbolicNode::NodePtr simplify(const SymbolicNode::NodePtr& original){
     
    if (auto* sum = dynamic_cast<const SymbolicSum*>(original.get())) {

        std::vector<SymbolicNode::NodePtr> elements;

        for (const auto& term : sum->getElements()) {

            if (term->kind() == NodeType::Negative) {

                auto* neg =
                    CASUtils::getSymbolicNodeOfType<const SymbolicNegativeNode>(term);

                elements.push_back(neg->getOriginal());

            } else {

                elements.push_back(
                    SymbolicNode::makeNode<SymbolicNegativeNode>(term)
                );
            }
        }

        return SymbolicNode::makeNode<SymbolicSum>(std::move(elements));
    }

    if (auto* neg =
            CASUtils::getSymbolicNodeOfType<const SymbolicNegativeNode>(original)) {
        return neg->getOriginal();
    }

    return SymbolicNode::makeNode<SymbolicNegativeNode>(original);
    }

};