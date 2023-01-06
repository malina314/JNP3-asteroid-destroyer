#ifndef ASTEROID_DESTROYER_ANIMATORSEQUENCE_H
#define ASTEROID_DESTROYER_ANIMATORSEQUENCE_H


#include "Animator.h"

#include <vector>

class AnimatorSequence {
    std::vector<Animator> animators;
    size_t currentAnimatorIndex;

public:
    AnimatorSequence() : animators(), currentAnimatorIndex(0) {}

    void addAnimator(const Animator &animator) {
        animators.push_back(animator);
    }

    void start() {
        if (animators.empty()) {
            return;
        }
        animators[currentAnimatorIndex].start();
    }

    void update() {
        if (animators.empty()) {
            return;
        }
        animators[currentAnimatorIndex].update();
        if (animators[currentAnimatorIndex].isFinished()) {
            currentAnimatorIndex++;
            if (currentAnimatorIndex >= animators.size()) {
                return;
            }
            animators[currentAnimatorIndex].start();
        }
    }

    float getValue() const {
        if (animators.empty()) {
            return 0;
        }
        return animators[currentAnimatorIndex].getValue();
    }

    bool isFinished() const {
        if (animators.empty()) {
            return true;
        }
        return currentAnimatorIndex >= animators.size();
    }

    void terminate() {
        if (animators.empty()) {
            return;
        }
        animators[currentAnimatorIndex].terminate();
    }
};


#endif //ASTEROID_DESTROYER_ANIMATORSEQUENCE_H
