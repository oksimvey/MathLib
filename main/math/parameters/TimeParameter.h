//
// Created by hapoe on 4/20/2026.
//

#ifndef MATHLIB_MAIN_TIMEPARAMETER_H
#define MATHLIB_MAIN_TIMEPARAMETER_H

#include "math/easing/EasingStyle.h"


template<typename T>
class TimeParameter {

public:

    const bool& shouldRepeat;
    const float& startTime;
    const float& duration;
    const T& startValue;
    const T& endValue;
    const Easing::EasingType& easingType;
    const bool& playback;

    TimeParameter(const bool& repeat,
                 const bool& playback,
                  const float& duration,
                  const T& startValue,
                  const T& endValue,
                  const Easing::EasingType& type,
                  const float& startTime)
       : shouldRepeat(repeat),
         startTime(startTime),
         duration(duration),
         startValue(startValue),
         endValue(endValue),
         easingType(type),
    playback(playback)
    {}





    T getCurrentValue(const float& time) const {

        if (endValue <= startValue) {
            return startValue;
        }

        float realtime = time - startTime;




        if (realtime < 0) {
            return startValue;
        }

        float dt;

        if (playback) {
            const float cycle = duration * 2.0f;

            if (shouldRepeat) {
                realtime = fmod(realtime, cycle);
            }
            else if (realtime >= cycle) {
                return startValue;
            }

            if (realtime <= duration) {
                dt = realtime / duration; // ida
            } else {
                dt = 1.0f - (realtime - duration) / duration; // volta
            }
        }
        else {
            if (shouldRepeat) {
                realtime = fmod(realtime, duration);
            } else if (realtime >= duration) {
                return endValue;
            }

            dt = realtime / duration;
        }

        const float easedTime = Easing::interpolate(easingType, dt);

        return startValue * (1.0f - easedTime) + endValue * easedTime;
    }

};

template<typename T>
static TimeParameter<T> constantTimeParam(const T& value) {
    return TimeParameter(false, false, 0, value, value, Easing::Linear, 0);
}


#endif //MATHLIB_MAIN_TIMEPARAMETER_H

