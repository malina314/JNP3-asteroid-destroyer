#ifndef ASTEROID_DESTROYER_GAMEOBJECT_H
#define ASTEROID_DESTROYER_GAMEOBJECT_H


#include "CircleCollider.h"
#include "Vec2.h"
#include "Sprite.h"
#include "BitmapsManager.h"
#include "BitmapNames.h"
#include "common/Singleton.h"
#include "common/constants.h"

#include <d2d1_3.h>
#include <wincodec.h>

class GameObject {
protected:
    Sprite sprite;
    CircleCollider collider;
    Vec2 velocity; // velocity of the object, that is, for both collider and sprite

public:
    GameObject(Vec2 position, BitmapNames bitmapName, Vec2 velocity, float radiusMargin, Vec2 colliderOffset)
            : sprite(bitmapName, position, constants::BitmapSizes[static_cast<int>(bitmapName)]),
              collider(sprite.getCenter() + colliderOffset  * constants::SCALE,
                       sprite.getMeanSize() / 2 - radiusMargin * constants::SCALE),
              velocity(velocity) {}

    GameObject(Vec2 position, BitmapNames bitmapName, Vec2 velocity, float radiusMargin)
            : GameObject(position, bitmapName, velocity, radiusMargin, Vec2()) {}

    GameObject(Vec2 position, BitmapNames bitmapName, Vec2 velocity)
            : GameObject(position, bitmapName, velocity, 0) {}

    explicit GameObject(BitmapNames bitmapName) : GameObject(Vec2(), bitmapName, Vec2()) {}

    virtual void update(float deltaTime) {
        Vec2 delta = velocity * constants::US_PER_FRAME_INV * constants::SPEED_FACTOR * deltaTime;
        sprite.move(delta);
        collider.move(delta);
    }

    void move(Vec2 pos) {
        sprite.move(pos);
        collider.move(pos);
    }

    virtual void Draw(ID2D1HwndRenderTarget *pTarget) {
        Singleton<BitmapsManager>::getInstance().Draw(pTarget, sprite.getBitmapName(), sprite.getD2D_RECT_F());
    }

    bool outOfScreen(Vec2 screenSize) const {
        return sprite.outOfScreen(screenSize);
    }

    const CircleCollider &getCollider() const {
        return collider;
    }

    const Sprite &getSprite() const {
        return sprite;
    }
};


#endif //ASTEROID_DESTROYER_GAMEOBJECT_H
