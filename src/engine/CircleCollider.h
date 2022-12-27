#ifndef ASTEROID_DESTROYER_CIRCLECOLLIDER_H
#define ASTEROID_DESTROYER_CIRCLECOLLIDER_H


#include "Vec2.h"

class CircleCollider {
public:
    Vec2 position;
    int radius;

    CircleCollider(Vec2 position, int radius) : position(position), radius(radius) {}

    bool collidesWith(const CircleCollider& other) const {
        return (position - other.position).length() < radius + other.radius;
    }
};


#endif //ASTEROID_DESTROYER_CIRCLECOLLIDER_H
