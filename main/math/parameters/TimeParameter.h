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
    const bool& playback;
    const bool isConst;

    TimeParameter(const bool& repeat,
                 const bool& playback,
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
    playback(playback),
    delay(delay),
    isConst(false)
    {}

    TimeParameter(const bool& repeat,
                const bool& playback,
                 const float& duration,
                 const float& startValue,
                 const float& endValue,
                 const Easing::EasingType& type,
                 const float& startTime,
                 const float& delay, const bool& isconst)
      : shouldRepeat(repeat),
        startTime(startTime),
        duration(duration),
        startValue(startValue),
        endValue(endValue),
        easingType(type),
   playback(playback),
   delay(delay),
   isConst(isconst)
    {}

    float getCurrentValue(const float& time) const {

        if (isConst) {
            return startValue;
        }

        float realtime = time - (startTime + delay);




        if (realtime < 0) {
            return startValue;
        }

        float dt;

        if (playback) {
            const float cycle = duration * 2.0f;

            if (shouldRepeat) {
                realtime = fmod(realtime, cycle);
            } else if (realtime >= cycle) {
                return startValue; // terminou o vai e volta
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

static TimeParameter constantTimeParam(const float& value) {

    return TimeParameter(false, false, 0, value, value, Easing::Linear, 0, 0, true);
}


#endif //MATHLIB_MAIN_TIMEPARAMETER_H

