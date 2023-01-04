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
    GameObject(Vec2 position, BitmapNames bitmapName, Vec2 velocity, float radiusMargin)
            : sprite(bitmapName, position, constants::BitmapSizes[static_cast<int>(bitmapName)]),
              collider(sprite.getCenter(), sprite.getMeanSize() / 2 - radiusMargin),
              velocity(velocity) {}

    GameObject(Vec2 position, BitmapNames bitmapName, Vec2 velocity)
            : GameObject(position, bitmapName, velocity, 0) {}


    explicit GameObject(BitmapNames bitmapName) : GameObject(Vec2(0, 0), bitmapName, Vec2(0, 0)) {}

    virtual void update() {
        // todo: velocity should be multiplied by delta time
        sprite.move(velocity);
        collider.move(velocity);
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
