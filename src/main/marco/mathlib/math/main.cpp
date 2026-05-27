
#include <iostream>
#include <ostream>

#include "windows.h"




#include "number/scalar/RealNumber.h"



int main() {

  SetConsoleOutputCP(CP_UTF8);

  RealNumber a(4);

  RealNumber b(0.5);

  std::cout << (a^b).toString()  << std::endl;

  return 0;
}