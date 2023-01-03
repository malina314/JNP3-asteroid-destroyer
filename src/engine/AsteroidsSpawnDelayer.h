#ifndef ASTEROID_DESTROYER_ASTEROIDSSPAWNDELAYER_H
#define ASTEROID_DESTROYER_ASTEROIDSSPAWNDELAYER_H


#include "Timer.h"
#include "common/constants.h"

class AsteroidsSpawnDelayer {
    bool locked;

public:
    AsteroidsSpawnDelayer() : locked(false) {}

    bool canSpawn() const {
        return !locked;
    }

    void lock() {
        if (locked) {
            return;
        }

        locked = true;
        Timer::setTimeout([this]() {
            locked = false;
        }, constants::ASTEROID_SPAWN_DELAY_MS);
    }
};


#endif //ASTEROID_DESTROYER_ASTEROIDSSPAWNDELAYER_H
