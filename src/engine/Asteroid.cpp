#include "Asteroid.h"

#include "Engine.h"
#include "GameObject.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "common/constants.h"
#include "common/Singleton.h"

#include <d2d1.h>
#include <d2d1helper.h>

Asteroid::Asteroid(Vec2 position, Vec2 velocity, BitmapNames bitmapName)
        : GameObject(position, bitmapName, velocity, constants::ASTEROID_RADIUS_MARGIN) {}

void Asteroid::Draw(ID2D1HwndRenderTarget *pTarget) {
    Vec2 center = sprite.getCenter();
    D2D1::Matrix3x2F tfMatrix = D2D1::Matrix3x2F::Rotation(calcAngle(), D2D1::Point2F(center.x, center.y));
    D2D1::Matrix3x2F tfMatrixInv = D2D1::Matrix3x2F::Rotation(0.0f, D2D1::Point2F(center.x, center.y));

    Singleton<BitmapsManager>::getInstance().DrawWithTransformation(
            pTarget, sprite.getBitmapName(), sprite.getD2D_RECT_F(), tfMatrix, tfMatrixInv);
}

float Asteroid::calcAngle() const {
    float time = Singleton<Engine>::getInstance().getTimeSinceStart().count();
    return time * constants::US_PER_FRAME_INV * constants::ASTEROID_ROTATION_SPEED;
}