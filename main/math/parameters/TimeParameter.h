//
// Created by hapoe on 4/20/2026.
//

#ifndef MATHLIB_MAIN_TIMEPARAMETER_H
#define MATHLIB_MAIN_TIMEPARAMETER_H

#include "math/easing/EasingStyle.h"


class TimeParameter {

public:

    const bool& shouldRepeat;
    float startTime;
    const float duration;
    const float startValue;
    const float endValue;
    const Easing::EasingType easingType;

    TimeParameter(const bool& repeat,
                  const float& duration,
                  const float& startValue,
                  const float& endValue,
                  const Easing::EasingType& type,
                  const float& startTime)
       : shouldRepeat(repeat),
         startTime(startTime),
         duration(duration),
         startValue(startValue),
         endValue(endValue),
         easingType(type)
    {}

    float getCurrentValue(const float& time) {
        float realtime = time - startTime;

        if (realtime > duration) {
            if (shouldRepeat) {
                startTime = time;
                realtime = 0;
            }
            else {
                return endValue;
            }
        }

        const float dt = realtime / duration; // normaliza 0..1
        const float easedTime = Easing::interpolate(easingType, dt);

        return startValue * (1.0f - easedTime) + endValue * easedTime;
    }




};


#endif //MATHLIB_MAIN_TIMEPARAMETER_H

