//
// Created by hapoe on 5/28/2026.
//
#pragma once
#include <vector>

#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"

#include "main/marco/mathlib/math/cas/simplifier/CASSimplifier.h"

class SumSimplifier;

class SymbolicSum : public SymbolicNode {
    
    std::vector<NodePtr> elements;

public:

std::vector<NodePtr> getElements() const {
    return elements;
}

    template <typename... Args>
        requires (std::is_convertible_v<Args, NodePtr> && ...)
    explicit SymbolicSum(Args... args) : elements{static_cast<NodePtr>(args)...} {}

    template <typename... Args>
    requires (std::is_convertible_v<Args, SymbolicNode*> && ...)
    explicit SymbolicSum(Args... args) : elements{static_cast<NodePtr>(args)...} {}


    [[nodiscard]] NodeType kind() const override {
        return NodeType::Addition;
    }

    static std::string replaceAll(std::string str,
                        const std::string& from,
                        const std::string& to) {

        size_t start = 0;

        while ((start = str.find(from, start)) != std::string::npos) {
            str.replace(start, from.length(), to);
            start += to.length();
        }

        return str;
    }

    [[nodiscard]] NodePtr simplify() const override {
        return CASSimplifier::simplifySum(elements);
    }

    [[nodiscard]] std::string toString() const override {

        std::string result;

        for (size_t i = 0; i < elements.size(); i++) {

            const double value = elements[i]->evaluate();

            if (value == 0) continue;


            if (i != 0 &&  i != elements.size()) {
                if (value < 0) {
                    result += " - " + replaceAll(elements[i]->toString(), "-", "");
                    continue;
                }
                result += " + ";
            }
            result += elements[i]->toString();
        }
        return result;
    };

    [[nodiscard]] std::string toLatexString() const override {
        return "";
    };

    [[nodiscard]] double evaluate() const override {
        double sum = 0;
        for (const NodePtr& node : elements) {
            sum += node->evaluate();
        }
        return sum;
    };
};
