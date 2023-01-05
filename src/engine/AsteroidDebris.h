#ifndef ASTEROID_DESTROYER_ASTEROIDDEBRIS_H
#define ASTEROID_DESTROYER_ASTEROIDDEBRIS_H

#include "Sprite.h"
#include "Vec2.h"
#include "BitmapNames.h"

#include <d2d1.h>

class AsteroidDebris {
    Sprite sprite;
    float scale;
    float opacity;

public:
    AsteroidDebris(Vec2 position, BitmapNames bitmapName, float scale, float opacity = constants::DEBRIS_OPACITY);

    void Draw(ID2D1HwndRenderTarget *pTarget);

    bool visible() const;

    void update();
};


#endif //ASTEROID_DESTROYER_ASTEROIDDEBRIS_H
