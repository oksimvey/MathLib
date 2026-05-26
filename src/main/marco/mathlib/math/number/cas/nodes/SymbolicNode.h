#ifndef SYMBOLIC_NODE_H
#define SYMBOLIC_NODE_H

#include <memory>
#include <string>



class SymbolicNode {

public:

 virtual ~SymbolicNode() = default;

    virtual std::string toString() = 0;

    virtual double evaluate() = 0;

};

using NodePtr = std::unique_ptr<SymbolicNode>;


template<typename T>
NodePtr makeNode(T&& value) {
    return std::make_unique<std::decay_t<T>>(
        std::forward<T>(value)
    );
}



#endif