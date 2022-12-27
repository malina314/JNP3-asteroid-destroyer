#ifndef ASTEROID_DESTROYER_BULLET_H
#define ASTEROID_DESTROYER_BULLET_H


#include "Movable.h"

class Bullet : public Movable {
public:
    Bullet(Vec2 position, Vec2 velocity) : Movable(position, velocity, CircleCollider(position, 10)) {}
};


#endif //ASTEROID_DESTROYER_BULLET_H
