#ifndef ASTEROID_DESTROYER_ASTEROIDDEBRIS_H
#define ASTEROID_DESTROYER_ASTEROIDDEBRIS_H

#include "Sprite.h"
#include "Vec2.h"
#include "BitmapNames.h"

#include <d2d1.h>

class AsteroidDebris {
    Sprite sprite;
    float scale;

public:
    AsteroidDebris(Vec2 position, BitmapNames bitmapName, float scale);

    void Draw(ID2D1HwndRenderTarget *pTarget);

    bool visible() const;

    void update();
};


#endif //ASTEROID_DESTROYER_ASTEROIDDEBRIS_H
