#ifndef SYMBOLIC_NODE_PAIR_H
#define SYMBOLIC_NODE_PAIR_H
#include "SymbolicNode.h"
#include <memory>

class SymbolicNodePair : public SymbolicNode {

    public:

        NodePtr left;
        NodePtr right;

         SymbolicNodePair(NodePtr left, NodePtr right)
        : left(std::move(left)),
          right(std::move(right)) {}


       
};




#endif