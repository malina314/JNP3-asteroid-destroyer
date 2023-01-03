#ifndef ASTEROID_DESTROYER_ASTEROID_H
#define ASTEROID_DESTROYER_ASTEROID_H


#include "GameObject.h"
#include "Vec2.h"
#include "BitmapNames.h"

class Asteroid : public GameObject {
public:
    Asteroid(Vec2 position, Vec2 velocity, BitmapNames bitmapName)
            : GameObject(position, bitmapName, velocity, 20) {}
};


#endif //ASTEROID_DESTROYER_ASTEROID_H
