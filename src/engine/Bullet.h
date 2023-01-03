#ifndef ASTEROID_DESTROYER_BULLET_H
#define ASTEROID_DESTROYER_BULLET_H


#include "GameObject.h"
#include "Vec2.h"
#include "BitmapNames.h"

class Bullet : public GameObject {
public:
    Bullet(Vec2 position, Vec2 velocity, BitmapNames bitmapName)
        : GameObject(position, bitmapName, velocity) {}
};


#endif //ASTEROID_DESTROYER_BULLET_H
