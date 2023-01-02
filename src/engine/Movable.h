#ifndef ASTEROID_DESTROYER_MOVABLE_H
#define ASTEROID_DESTROYER_MOVABLE_H


#include "CircleCollider.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "Singleton.h"
#include "BitmapsManager.h"

#include <d2d1_3.h>
#include <wincodec.h>
#include <functional>

class Movable {
public:
    Vec2 position;
    Vec2 velocity;
    CircleCollider collider;
    BitmapNames bitmapName;

    Movable(Vec2 position, Vec2 velocity, CircleCollider collider, BitmapNames bitmapName)
            : position(position), velocity(velocity), collider(collider), bitmapName(bitmapName) {}

    Movable(Vec2 position, int colliderRadius, BitmapNames bitmapName)
            : position(position), velocity(), collider(CircleCollider(position, colliderRadius)),
              bitmapName(bitmapName) {}

    virtual void update() {
        // todo: velocity should be multiplied by delta time
        position = position + velocity;
        collider.position = collider.position + velocity;
    }

    void Draw(ID2D1HwndRenderTarget *pTarget) {
        Singleton<BitmapsManager>::getInstance().Draw(pTarget, bitmapName, makeRectF());
    }

private:
    D2D_RECT_F makeRectF() const {
        return D2D1::RectF(position.x - collider.radius / 2,
                           position.y - collider.radius / 2,
                           position.x + collider.radius / 2,
                           position.y + collider.radius / 2);
    }
};


#endif //ASTEROID_DESTROYER_MOVABLE_H
