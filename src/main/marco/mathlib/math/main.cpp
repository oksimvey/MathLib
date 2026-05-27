#include "number/cas/utils/Parser.h"
#include "windows.h"
#include "number/scalar/RealNumber.h"
#include <iostream>

auto main() -> int {

  SetConsoleOutputCP(CP_UTF8);

 
  RealNumber a = Parser::fromString("1 + 2.5");


 

  std::cout << a.toString() << std::endl;


  return 0;
}
