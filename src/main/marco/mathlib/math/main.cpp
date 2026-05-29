#include "cas/number/RealNumber.h"
#include <array>
#include <bit>
#include <iostream>
#include <ostream>
#include <winsock.h>

int main(){

  
  RealNumber a = 2.0/3;

  RealNumber b = 4.0/3;



  std::cout << a.value->toString() << std::endl;

  std::cout << b.value->toString() << std::endl;

  std::cout << (a+b).value->toString() << std::endl;


}