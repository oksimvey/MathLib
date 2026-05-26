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

using NodePtr = std::shared_ptr<SymbolicNode>;

template<typename T, typename... Args>
NodePtr makeNode(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}



#endif