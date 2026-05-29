#include "cas/number/RealNumber.h"
#include <array>
#include <bit>
#include <iostream>
#include <ostream>
#include <winsock.h>

int main(){

  RealNumber result = 0.1f;

  std::cout << result.value->toString() << std::endl;
  std::cout << result.value->evaluate() << std::endl;
}