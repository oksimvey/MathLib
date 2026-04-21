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
    const float delay;

    TimeParameter(const bool& repeat,
                  const float& duration,
                  const float& startValue,
                  const float& endValue,
                  const Easing::EasingType& type,
                  const float& startTime,
                  const float& delay)
       : shouldRepeat(repeat),
         startTime(startTime),
         duration(duration),
         startValue(startValue),
         endValue(endValue),
         easingType(type),
    delay(delay)
    {}
    float getCurrentValue(const float& time) const {
        float realtime = time - (startTime+delay);

        if (realtime < 0) {
            return startValue;
        }

        if (shouldRepeat) {
            realtime = fmod(realtime, duration);
        }
        else {
            if (realtime > duration) {
                return endValue;
            }
        }

        const float dt = realtime / duration;
        const float easedTime = Easing::interpolate(easingType, dt);

        return startValue * (1.0f - easedTime) + endValue * easedTime;
    }




};


#endif //MATHLIB_MAIN_TIMEPARAMETER_H

