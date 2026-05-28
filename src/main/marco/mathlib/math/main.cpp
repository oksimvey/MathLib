#include "number/cas/utils/Parser.h"
#include "windows.h"
#include "number/scalar/RealNumber.h"
#include <iostream>

auto main() -> int {

  SetConsoleOutputCP(CP_UTF8);

 
  RealNumber a(0.666);


 RealNumber result = a;

  std::cout << result.toString() << std::endl;

  std::cout << result.evaluate() << std::endl;

  return 0;
}
