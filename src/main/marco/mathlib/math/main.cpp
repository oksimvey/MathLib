#include "cas/number/RealNumber.h"
#include <array>
#include <bit>
#include <iostream>
#include <ostream>
#include <winsock.h>

int main(){

  
  RealNumber a = 1.5;

  RealNumber b = 2;

  RealNumber c = -3.5;

  c = -c;

  RealNumber t = -4;

  RealNumber d = a + (b  - (c - t + t - (a + b)));

 std::cout << d.value->toString() << std::endl;


  std::cout << d.value->evaluate() << std::endl;


}