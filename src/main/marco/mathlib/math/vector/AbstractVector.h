#ifndef ABSTRACT_VECTOR_H
#define ABSTRACT_VECTOR_H
#include <type_traits>
#include "../number/scalar/RealNumber.h"
#include "../number/scalar/ComplexNumber.h"
#include "../number/scalar/Scalar.h"


template <int Dimension, typename ScalarType>
class AbstractVector {

     

       
       static_assert(Dimension > 0, "Dimension must be greater than 0");

       static_assert(Scalar::isScalar<ScalarType>, "Invalid scalar type");


       const ScalarType components[Dimension];

       public:

       AbstractVector(const ScalarType components[Dimension]) : components(components) {}

       AbstractVector() : AbstractVector({0}) {}

       

       


       









};

#endif // ABSTRACT_VECTOR_H