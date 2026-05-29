//
// Created by hapoe on 5/28/2026.


#pragma once

template<typename T>
struct Scalar {

    virtual T operator+(const T& other) const = 0;

    virtual T operator-(const T& other) const = 0;

    virtual T operator*(const T& other) const = 0;

    virtual T operator/(const T& other) const = 0;




};