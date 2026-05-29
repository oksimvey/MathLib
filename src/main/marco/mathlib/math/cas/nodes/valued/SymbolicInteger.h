//
// Created by hapoe on 5/28/2026.
//
#pragma once
#include "main/marco/mathlib/math/cas/nodes/SymbolicNode.h"
#include <memory>

class SymbolicInteger : public SymbolicNode {

    const int value;

public:
    explicit SymbolicInteger(const int& value_) : value(value_) {}

    [[nodiscard]] NodeType kind() const override {
        return NodeType::Integer;
    }

    [[nodiscard]] SymbolicNode::NodePtr simplify() const override {
        return std::make_shared<SymbolicInteger>(value);
    }

    [[nodiscard]] std::string toString() const override {
        return std::to_string(value);
    };

    [[nodiscard]] std::string toLatexString() const override {
        return "";
    };

    [[nodiscard]] double evaluate() const override {
        return value;
    };
};
