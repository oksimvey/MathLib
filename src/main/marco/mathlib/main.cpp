
#include <iostream>
#include "RealNumber.h"




int main() {

    int a = 4;

    int* b = &a;

   *b = 7;


   RealNumber num1(2, 0);

   RealNumber num2(3, 0);

   RealNumber result = num1 + num2;





  

    std::cout << a << std::endl;

    std::cout << *b << std::endl;




    


    
    return 0;
}
