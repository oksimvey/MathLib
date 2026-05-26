
#include <algorithm>
#include <iostream>
#include <ostream>
#include "windows.h"
#include "number/cas/SymbolicInteger.h"

#include "number/cas/SymbolicSqrt.h"

#include "number/cas/SymbolicPow.h"

#include "number/cas/SymbolicFraction.h"

#include "number/RealNumber.h"


int main() {

    SetConsoleOutputCP(CP_UTF8);

  RealNumber a(1);

  RealNumber b(2);

  std::cout << ((a + b)/(b.sqrt())).node->toString() << std::endl;

  std::cout << ((a + b)/b).node->evaluate() << std::endl;

 
 

  





  return 0;
}