#ifndef ABSTRACT_VECTOR_H
#define ABSTRACT_VECTOR_H
#include "main/marco/mathlib/math/cas/number/Scalar.h"
#include <array>
#include <type_traits>


template <int Dimension, typename ScalarType>
class AbstractVector {

     

       
       static_assert(Dimension > 0, "Dimension must be greater than 0");


       const std::array<ScalarType, Dimension> components;

       public:

       AbstractVector(const ScalarType components[Dimension]) : components(components) {}

       AbstractVector() : AbstractVector({0}) {}

       

       


       









};

#endif // ABSTRACT_VECTOR_H