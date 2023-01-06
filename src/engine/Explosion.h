#ifndef ASTEROID_DESTROYER_EXPLOSION_H
#define ASTEROID_DESTROYER_EXPLOSION_H


#include "Animator.h"
#include "Vec2.h"
#include "common/constants.h"
#include "common/utils.h"

#include <chrono>

class Explosion {
    // Animator for explosion scale
    Animator appear;
    Animator disappear;
    Animator &currentAnimator;
    Vec2 position;

public:
    explicit Explosion(Vec2 position) : appear(0, 1, utils::duration{constants::EXPLOSION_APPEAR_DURATION}),
            disappear(1, 0, utils::duration{constants::EXPLOSION_DISAPPEAR_DURATION}),
            currentAnimator(appear), position(position) {
        currentAnimator.start();
    }

    Explosion &operator=(const Explosion &other) {
        if (this != &other) { // not a self-assignment
            appear = other.appear;
            disappear = other.disappear;
            if (other.currentAnimator.equal(other.appear)) {
                currentAnimator = appear;
            } else {
                currentAnimator = disappear;
            }
            position = other.position;
        }

        return *this;
    }

    void update() {
        if (isFinished()) {
            LOG("Finished");
            return;
        }

        // This shouldn't happen, but just in case
//        if (&currentAnimator != &appear && &currentAnimator != &disappear) {
//            currentAnimator = disappear;
//            currentAnimator.terminate();
//            LOG("Explosion animator is in unknown state");
//            return;
//        }

        currentAnimator.update();

        if (currentAnimator.isFinished() && currentAnimator.equal(appear)) {
            currentAnimator = disappear;
            currentAnimator.start();
            LOG("Explosion disappear started");
        }
    }

    float getScale() const {
        return currentAnimator.getValue();
    }

    bool isFinished() const {
        return disappear.isFinished();
    }

    Vec2 getPosition() const {
        return position;
    }

    void Draw() const;
};


#endif //ASTEROID_DESTROYER_EXPLOSION_H
