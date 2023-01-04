#include "Asteroid.h"

#include "Engine.h"
#include "GameObject.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "common/constants.h"
#include "common/Singleton.h"

#include <cstdint>
#include <d2d1.h>

Asteroid::Asteroid(Vec2 position, Vec2 velocity, BitmapNames bitmapName)
        : GameObject(position, bitmapName, velocity, constants::ASTEROID_RADIUS_MARGIN) {}

void Asteroid::Draw(ID2D1HwndRenderTarget *pTarget) {
Singleton<BitmapsManager>::getInstance().DrawWithRotation(
        pTarget, sprite.getBitmapName(), sprite.getD2D_RECT_F(), calcAngle(), sprite.getCenter());
}

float Asteroid::calcAngle() const {
    uint64_t time = Singleton<Engine>::getInstance().getTimeSinceStart().count();
    return static_cast<float>(time) * constants::NS_PER_FRAME_INV * constants::ASTEROID_ROTATION_SPEED;
}