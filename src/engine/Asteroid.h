#ifndef ASTEROID_DESTROYER_ASTEROID_H
#define ASTEROID_DESTROYER_ASTEROID_H


#include "Movable.h"
#include "Vec2.h"
#include "BitmapsManager.h"

class Asteroid : public Movable {
public:
    Asteroid(Vec2 position, Vec2 velocity, BitmapNames bitmapName)
        : Movable(position, velocity, CircleCollider(position, 200), bitmapName) {}
};


#endif //ASTEROID_DESTROYER_ASTEROID_H
