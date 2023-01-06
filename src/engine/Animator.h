#ifndef ASTEROID_DESTROYER_ANIMATOR_H
#define ASTEROID_DESTROYER_ANIMATOR_H


#include "common/utils.h"

#include <chrono>

class Animator {
    float value;
    float beginValue;
    float endValue;
    utils::duration duration;
    utils::time_point startTime;
    bool finished;

public:
    Animator(float beginValue, float endValue, utils::duration duration)
            : value(beginValue), beginValue(beginValue), endValue(endValue),
              duration(duration), startTime(), finished(false) {}

    void start() {
        startTime = std::chrono::system_clock::now();
    }

    void update() {
        if (finished) {
            return;
        }
        utils::time_point currentTime = std::chrono::system_clock::now();
        utils::duration timePassed = currentTime - startTime;
        if (timePassed >= duration) {
            finished = true;
            value = endValue;
            return;
        }
        auto progress = timePassed / duration;
        value = beginValue + (endValue - beginValue) * progress;
    }

    float getValue() const {
        return value;
    }

    bool isFinished() const {
        return finished;
    }

    void terminate() {
        finished = true;
        value = endValue;
    }

    bool equal(const Animator &other) const {
        return beginValue == other.beginValue && endValue == other.endValue && duration == other.duration;
    }
};


#endif //ASTEROID_DESTROYER_ANIMATOR_H
