#ifndef ASTEROID_DESTROYER_ASTEROID_H
#define ASTEROID_DESTROYER_ASTEROID_H


#include "Movable.h"

class Asteroid : public Movable {
public:
    Asteroid(Vec2 position, Vec2 velocity) : Movable(position, velocity, CircleCollider(position, 200)) {}
};


#endif //ASTEROID_DESTROYER_ASTEROID_H
