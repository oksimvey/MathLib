#ifndef LINEAR_TRANSFORMATION_H
#define LINEAR_TRANSFORMATION_H

#include "AbstractTransformation.h"
#include "../number/Scalar.h"

template <typename ScalarType, int lines, int collums>
class LinearTransformation : public AbstractTransformation<ScalarType, lines, collums> {


    const std::array<ScalarType, lines * collums> components;

    public:

      static_assert(lines > 0, "Input Dimension must be greater than 0");

    static_assert(collums > 0, "Output Dimension must be greater than 0");

    static_assert(Scalar::isScalar<ScalarType>, "Invalid scalar type");



    ScalarType getComponent(const int& line, const int& collum) {
        return components[collum + line * collums];
    }



};


#endif