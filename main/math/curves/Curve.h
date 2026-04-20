#ifndef CURVE_H
#define CURVE_H

template<int dim>
class Curve {

    public:

    Curve();

    virtual AbstractVector<dim> getPoint(float t) = 0;

};

#endif