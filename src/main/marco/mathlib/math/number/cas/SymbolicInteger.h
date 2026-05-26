#ifndef SYMBOLIC_INTEGER
#define SYMBOLIC_INTEGER

#include "nodes/SymbolicNode.h"

class SymbolicInteger : public SymbolicNode {

    public:

    const int value;

    SymbolicInteger(int value) : value(value) {}

    std::string toString() override {
        return std::to_string(value);
    }

    double evaluate() override {
        return value;
    }
};

#endif