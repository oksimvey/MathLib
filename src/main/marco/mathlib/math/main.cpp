
#include <algorithm>
#include <iostream>
#include <ostream>
#include "windows.h"
#include "number/cas/SymbolicInteger.h"

#include "number/cas/SymbolicSqrt.h"

#include "number/cas/SymbolicPow.h"

#include "number/cas/SymbolicFraction.h"


int main() {

   SetConsoleOutputCP(CP_UTF8);

  SymbolicSqrt sqrt(makeNode(SymbolicInteger(2)));


  SymbolicInteger a = SymbolicInteger(2);

  SymbolicInteger b(3);

  SymbolicPow e = SymbolicPow(makeNode(a), makeNode(  b));

  

    SymbolicPow c(
    makeNode(std::move(sqrt)),
    makeNode(std::move(e))
  );

  SymbolicFraction f(makeNode(a), makeNode(std::move(c)));


  std::cout << f.toString()<< std::endl;

  





  return 0;
}