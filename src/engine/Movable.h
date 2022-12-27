#ifndef ASTEROID_DESTROYER_MOVABLE_H
#define ASTEROID_DESTROYER_MOVABLE_H


#include "CircleCollider.h"
#include "Vec2.h"

class Movable {
public:
    Vec2 position;
    Vec2 velocity;
    CircleCollider collider;

    Movable(Vec2 position, Vec2 velocity, CircleCollider collider)
            : position(position), velocity(velocity), collider(collider) {}

    Movable(Vec2 position, int colliderRadius)
            : position(position), velocity(), collider(CircleCollider(position, colliderRadius)) {}

    virtual void update() {
        // todo: velocity should be multiplied by delta time
        position = position + velocity;
        collider.position = collider.position + velocity;
    }
};


#endif //ASTEROID_DESTROYER_MOVABLE_H
