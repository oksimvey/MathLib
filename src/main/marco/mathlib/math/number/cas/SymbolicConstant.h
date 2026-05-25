#ifndef SYMBOLIC_CONSTANT_H
#define SYMBOLIC_CONSTANT_H


#include <string>
#include "SymbolicComponent.h"

template<typename T>
class SymbolicConstant : public SymbolicComponent<T> {

    const std::string symbol;

    public:

    static_assert(std::is_arithmetic<T>::value, "SymbolicConstant requires an arithmetic type");

    SymbolicConstant(T value, std::string sym) : SymbolicComponent<T>(value), symbol(sym) {}

    std::string toString() const override {
        return symbol;
    }

    T evaluate() const override {
        return this->value;
    }

 };
#endif