#include "AsteroidDebris.h"

#include "Vec2.h"
#include "Sprite.h"
#include "BitmapsManager.h"
#include "BitmapNames.h"
#include "common/constants.h"
#include "common/Singleton.h"

#include <d2d1.h>
#include <d2d1helper.h>

AsteroidDebris::AsteroidDebris(Vec2 position, BitmapNames bitmapName, float scale)
    : sprite(bitmapName, position, constants::BitmapSizes[static_cast<int>(bitmapName)]),
      scale(scale) {}

void AsteroidDebris::Draw(ID2D1HwndRenderTarget *pTarget) {
    if (!visible()) {
        return;
    }

    Vec2 center = sprite.getCenter();
    D2D1::Matrix3x2F tfMatrix = D2D1::Matrix3x2F::Scale(scale, scale, D2D1::Point2F(center.x, center.y));
    D2D1::Matrix3x2F tfMatrixInv = D2D1::Matrix3x2F::Scale(1.0f / scale, 1.0f / scale, D2D1::Point2F(center.x, center.y));

    Singleton<BitmapsManager>::getInstance().DrawWithTransformation(
            pTarget, sprite.getBitmapName(), sprite.getD2D_RECT_F(), tfMatrix, tfMatrixInv, constants::DEBRIS_OPACITY);
}

bool AsteroidDebris::visible() const {
    return scale > constants::DEBRIS_VISIBILITY_THRESHOLD;
}

void AsteroidDebris::update() {
    scale -= constants::DEBRIS_DISAPPEARING_SPEED;
}
