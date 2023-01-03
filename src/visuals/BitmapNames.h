#ifndef ASTEROID_DESTROYER_BITMAPNAMES_H
#define ASTEROID_DESTROYER_BITMAPNAMES_H


#include "Vec2.h"

enum class BitmapNames {
    PLAYER,
    BACKGROUND,
    BULLET,
    ASTEROID1,
    ASTEROID2,
    ASTEROID3,
    Count // special value used for declaring arrays
};

namespace {
    const Vec2 BitmapSizes[] = {
        Vec2(142, 150),     // PLAYER
        Vec2(1920, 1080),   // BACKGROUND
        Vec2(20, 20),       // BULLET
        Vec2(400, 400),     // ASTEROID1
        Vec2(400, 400),     // ASTEROID2
        Vec2(400, 400)      // ASTEROID3
    };
}

#endif //ASTEROID_DESTROYER_BITMAPNAMES_H
