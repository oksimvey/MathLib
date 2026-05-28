#pragma once

#include <stdexcept>
#include <string>
#include "../nodes/SymbolicNode.h"
#include "../nodes/SymbolicNodePair.h"

class CASUtils {

    public:


    static bool isSymbolicNodePair(const SymbolicNode::NodePtr& node) {
        return dynamic_cast<const SymbolicNodePair*>(node.get()) != nullptr;
    };

    template<typename T>
    static T* getSymbolicNodeOfType(const SymbolicNode::NodePtr& node) {
            return dynamic_cast<T*>(node.get());
    }


    template<typename T>
    static bool isSymbolicNodeOfType(const SymbolicNode::NodePtr& node) {
        return getSymbolicNodeOfType<T>(node) != nullptr;
    }

    template<typename T>
    static bool areBothNodesOfType(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return isSymbolicNodeOfType<T>(node1) && isSymbolicNodeOfType<T>(node2);
    }

    static std::string getStringAsChildren(const SymbolicNode::NodePtr& node) {
        if (isSymbolicNodePair(node)) {
            return "(" + node-> toString() + ")";
        }
        return node->toString();
    }

    template<typename T>
    static std::string getAsChildrenIfType(const SymbolicNode::NodePtr& node) {
        if (isSymbolicNodeOfType<T>(node)) {
            return "(" + node-> toString() + ")";
        }
        return node->toString();
    }
};