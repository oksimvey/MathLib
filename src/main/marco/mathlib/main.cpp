
#include <vector>
#include <cmath>
#include <iostream>
#include "RealNumber.h"


void printValue(float value){

    std::cout << "The value is: " << value << std::endl;
}

void printPointer(float value){

    
    float* ptr = &value;

    std::cout << "The adress is: " << ptr << std::endl;
}

int main() {





  

    RealNumber a(0.3 + 0.2 + 0.1);

    RealNumber b(4, 1);

    std::cout << "A: " << a.toString() << std::endl;

    std::cout << "B: " << b.toString() << std::endl;

    std::cout << "A + B: " << (a + b).toString() << std::endl;

   
    std::cout << (a == b) << std::endl;




    


    
    return 0;
}
