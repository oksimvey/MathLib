#ifndef SYMBOLIC_COMPONENT_H
#define SYMBOLIC_COMPONENT_H

#include <string>

template <typename T> class SymbolicComponent {

public:
  const T value;

 



  static_assert(std::is_arithmetic<T>::value, "SymbolicComponent requires an arithmetic type");

  SymbolicComponent(T value) : value(value) {}

  virtual std::string toString() const = 0;

  virtual T evaluate() const = 0;
};

#endif