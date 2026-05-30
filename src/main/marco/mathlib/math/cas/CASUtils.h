#pragma once

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include "nodes/NodeType.h"
#include "nodes/SymbolicNode.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
class CASUtils
{

  public:
    static constexpr std::array<NodeType, 2> multipleNodeTypes = {NodeType::Sum,
                                                                  NodeType::Multiply};

    static int countDecimalDigits(double value)
    {
        value = std::fabs(value);

        std::ostringstream oss;

        oss << std::fixed << std::setprecision(9) << value;

        std::string s = oss.str();

        size_t dot = s.find('.');
        if (dot == std::string::npos)
            return 0;

        std::string decimals = s.substr(dot + 1);

        while (!decimals.empty() && decimals.back() == '0')
            decimals.pop_back();

        return decimals.size();
    }

    template <typename T> static T* getSymbolicNodeOfType(const SymbolicNode::NodePtr& node)
    {
        return dynamic_cast<T*>(node.get());
    }

    template <typename T> static bool isSymbolicNodeOfType(const SymbolicNode::NodePtr& node)
    {
        return getSymbolicNodeOfType<T>(node) != nullptr;
    }

    template <typename T>
    static bool areBothNodesOfType(const SymbolicNode::NodePtr& node1,
                                   const SymbolicNode::NodePtr& node2)
    {
        return isSymbolicNodeOfType<T>(node1) && isSymbolicNodeOfType<T>(node2);
    }

    static bool isMultipleNode(const SymbolicNode::NodePtr& node)
    {
        return std::ranges::contains(multipleNodeTypes, node->kind());
    }

    static std::string getWithParenthesisIfMultiple(const SymbolicNode::NodePtr& node)
    {
        if (isMultipleNode(node))
        {
            return "(" + node->toString() + ")";
        }
        return node->toString();
    }
};