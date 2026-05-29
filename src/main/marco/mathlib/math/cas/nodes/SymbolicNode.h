//
// Created by hapoe on 5/28/2026.
//
#pragma once
#include <memory>
#include <string>

#include "NodeType.h"

class SymbolicNode {

public:

    using NodePtr = std::shared_ptr<const SymbolicNode>;

    virtual ~SymbolicNode() = default;

    template<typename T, typename... Args>
    static NodePtr makeNode(Args&&... args) {
        return std::make_shared<T>(
            std::forward<Args>(args)...
        );
    }





    [[nodiscard]] virtual NodeType kind() const = 0;

    [[nodiscard]] virtual std::string toString() const = 0;

    [[nodiscard]] virtual std::string toLatexString() const = 0;

    [[nodiscard]] virtual NodePtr simplify() const  = 0;

    [[nodiscard]] virtual double evaluate() const = 0;

};
