#ifndef CURVE_H
#define CURVE_H

template <int dim>
class Curve {

    public:

    Curve();

    virtual AbstractVector<dim> getPoint(float t) = 0;

    virtual std::array<float, 4> getColor(float t) = 0;

    virtual AbstractVector<dim> getTangent(float t) = 0;

    virtual AbstractVector<dim> getNormal(float t) = 0;

    virtual float getLength() = 0;




};

#endif