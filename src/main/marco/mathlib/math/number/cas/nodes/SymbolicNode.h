#ifndef SYMBOLIC_NODE_H
#define SYMBOLIC_NODE_H

#include <memory>
#include <string>

class SymbolicNode {

public:

  virtual ~SymbolicNode() = default;

  virtual std::string toString() const = 0;

  virtual std::string toLatex() const = 0;

  using NodePtr = std::shared_ptr<SymbolicNode>;

  virtual NodePtr simplify() const = 0;

  virtual double evaluate() const = 0;

  template <typename T, typename... Args>
  static NodePtr makeNode(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
};

#endif