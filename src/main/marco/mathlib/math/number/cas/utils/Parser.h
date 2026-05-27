#pragma once

#include "main/marco/mathlib/math/number/scalar/RealNumber.h"

#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Parser
{
public:


    static std::unordered_map<char, SymbolicNode::NodePtr(*)(const SymbolicNode::NodePtr&, const SymbolicNode::NodePtr&)> operations;

    static SymbolicNode::NodePtr operationSum(const SymbolicNode::NodePtr& node1, const SymbolicNode::NodePtr& node2) {
        return SymbolicNode::makeNode<SymbolicSum>(node1, node2);
    }

   static void initOperations() {
       operations['+'] = operationSum;
   }

    static std::unordered_map<std::string, SymbolicNode::NodePtr(*)(const SymbolicNode::NodePtr&, const SymbolicNode::NodePtr&)> functions;

    static void initFunctions() {
        functions["sin"] = nullptr;
    }

    static constexpr bool isDigit(char c) {
        return (c >= '0' && c <= '9') || c == '.';
    }

    static double safeStod(const std::string& s) {
        std::cout << "stod input = [" << s << "]\n";

        if (s.empty()) {
            throw std::runtime_error("EMPTY TOKEN");
        }

        return std::stod(s);
    }

    static double parseDoubleFromLeft(const std::string& str, size_t pos) {
        size_t i = pos;
        while (i > 0 && isDigit(str[i - 1])) {
            i--;
        }

        const std::string token = str.substr(i, pos - i);
        return safeStod(token);
    }

    static double parseDoubleFromRight(const std::string& str, size_t pos) {
        size_t i = pos;

        while (i + 1 < str.length() && isDigit(str[i + 1])) {
            i++;
        }

        const std::string token = str.substr(pos, i - pos + 1);
        return safeStod(token);
    }
};
