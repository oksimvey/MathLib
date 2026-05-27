
#include <iostream>
#include <ostream>

#include "number/cas/operations/SymbolicFraction.h"
#include "windows.h"

#include "number/scalar/RealNumber.h"



int main() {

  SetConsoleOutputCP(CP_UTF8);

  const RealNumber a(4);

  const RealNumber b(0.5);

  std::cout << (a^b).toString()  << std::endl;

  return 0;
}