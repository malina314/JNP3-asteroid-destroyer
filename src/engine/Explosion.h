#ifndef ASTEROID_DESTROYER_EXPLOSION_H
#define ASTEROID_DESTROYER_EXPLOSION_H


#include "Animator.h"
#include "AnimatorSequence.h"
#include "Vec2.h"
#include "common/constants.h"
#include "common/utils.h"

#include <chrono>

class Explosion {
    AnimatorSequence scaleAnimator;
    Vec2 position;

public:
    explicit Explosion(Vec2 position, float scale = 1.0f) : scaleAnimator(), position(position) {
        scaleAnimator.addAnimator(Animator(0, scale, utils::duration{constants::EXPLOSION_APPEAR_DURATION}));
        scaleAnimator.addAnimator(Animator(scale, 0, utils::duration{constants::EXPLOSION_DISAPPEAR_DURATION}));
        scaleAnimator.start();
    }

    void update() {
        if (isFinished()) {
            return;
        }
        scaleAnimator.update();
    }

    float getScale() const {
        return scaleAnimator.getValue();
    }

    bool isFinished() const {
        return scaleAnimator.isFinished();
    }

    Vec2 getPosition() const {
        return position;
    }

    void Draw() const;
};


#endif //ASTEROID_DESTROYER_EXPLOSION_H
