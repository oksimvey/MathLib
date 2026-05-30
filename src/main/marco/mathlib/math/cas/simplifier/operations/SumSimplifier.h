#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "main/marco/mathlib/math/cas/nodes/operations/SymbolicSum.h"
#include <vector>


class SumSimplifier {

  static std::vector<SymbolicNode::NodePtr>
  aclopateSumNodes(const std::vector<SymbolicNode::NodePtr> &elements) {
    std::vector<SymbolicNode::NodePtr> toReturn;

    for (const SymbolicNode::NodePtr &element : elements) {

      const SymbolicNode::NodePtr simplfiied = element->simplify();

      if (auto *d = dynamic_cast<const SymbolicSum *>(simplfiied.get())) {
        auto sumElements = d->getElements();
        toReturn.insert(toReturn.end(), sumElements.begin(), sumElements.end());
        continue;
      }
     toReturn.push_back(simplfiied);
    }

    return toReturn;
  }

public:
  static SymbolicNode::NodePtr
  simplify(const std::vector<SymbolicNode::NodePtr> &elements) {
    std::vector<SymbolicNode::NodePtr> accloped = aclopateSumNodes(elements);
    return SymbolicNode::makeNode<SymbolicSum>(accloped);
  }
};