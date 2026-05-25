#ifndef MATHLIB_SCALAR_H
#define MATHLIB_SCALAR_H


template <typename ValueType>
class Scalar {

    const ValueType value;

    Scalar(const ValueType& value) : value(value) {}

    ValueType getValue() const {
        return value;
    }




    public:


};

#endif // MATHLIB_SCALAR_H