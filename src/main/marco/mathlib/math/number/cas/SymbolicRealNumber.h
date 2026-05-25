#ifndef SYMBOLIC_REAL_NUMBER_H
#define SYMBOLIC_REAL_NUMBER_H

#include <string>
#include <type_traits>
template<typename T>

class SymbolicRealNumber {

    public:

    static_assert(std::is_arithmetic<T>::value, "SymbolicRealNumber requires an arithmetic type");



    
   
};


#endif