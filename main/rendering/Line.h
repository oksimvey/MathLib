//
// Created by hapoe on 4/19/2026.
//

#ifndef MATHLIB_MAIN_LINE_H
#define MATHLIB_MAIN_LINE_H

class Line {
public:

    float arr[9] = {};

    Line(const float& x1_, const float& y1_, const float& x2_, const float& y2_,const float& r_, const float& g_, const float& b_, const float& a_, const float& thickness_) {
        arr[0] = x1_;
        arr[1] = y1_;
        arr[2] = x2_;
        arr[3] = y2_;
        arr[4] = r_;
        arr[5] = g_;
        arr[6] = b_;
        arr[7] = a_;
        arr[8] = thickness_;
    }

     float x1() const {
        return arr[0];
    }

    float y1() const {
        return arr[1];
    }

    float x2() const {
        return arr[2];
    }

    float y2() const {
        return arr[3];
    }

    float r() const {
        return arr[4];
    }

    float g() const {
        return arr[5];
    }

    float b() const {
        return arr[6];
    }

    float a() const {
        return arr[7];
    }

    float thickness() const {
        return arr[8];
    }
};

#endif
