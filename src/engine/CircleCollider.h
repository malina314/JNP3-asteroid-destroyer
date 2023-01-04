#ifndef ASTEROID_DESTROYER_CIRCLECOLLIDER_H
#define ASTEROID_DESTROYER_CIRCLECOLLIDER_H


#include "Vec2.h"

class CircleCollider {
    Vec2 position; // center of the circle
    float radius;

public:
    CircleCollider(Vec2 position, float radius) : position(position), radius(radius) {}

    bool collidesWith(const CircleCollider& other) const {
        return (position - other.position).length() < radius + other.radius;
    }

    void move(Vec2 delta) {
        position = position + delta;
    }

    Vec2 getPosition() const {
        return position;
    }
};


#endif //ASTEROID_DESTROYER_CIRCLECOLLIDER_H
