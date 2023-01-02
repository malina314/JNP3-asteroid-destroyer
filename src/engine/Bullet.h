#ifndef ASTEROID_DESTROYER_BULLET_H
#define ASTEROID_DESTROYER_BULLET_H


#include "Movable.h"
#include "Vec2.h"
#include "BitmapsManager.h"

class Bullet : public Movable {
public:
    Bullet(Vec2 position, Vec2 velocity, BitmapNames bitmapName)
        : Movable(position, velocity, CircleCollider(position, 10), bitmapName) {}
};


#endif //ASTEROID_DESTROYER_BULLET_H
