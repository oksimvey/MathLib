
#include "number/cas/SymbolicConstant.h"
#include "number/cas/SymbolicConstants.h"
#include "number/cas/SymbolicPow.h"
#include <iostream>
#include <string>

int main() {


  const SymbolicConstant<float> &pi = SymbolicConstants::PhiF;


  std::string pistr = SymbolicConstants::constants[1];

  std::cout << pi.toString() << "=" << std::to_string(pi.evaluate())
            << std::endl;

  return 0;
}