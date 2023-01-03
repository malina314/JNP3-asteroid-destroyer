#ifndef ASTEROID_DESTROYER_SPRITE_H
#define ASTEROID_DESTROYER_SPRITE_H


#include "Vec2.h"
#include "BitmapNames.h"

#include <d2d1_3.h>
#include <wincodec.h>

class Sprite {
    constexpr static int SCALE_DIV = 2;
    BitmapNames bitmapName;
    Vec2 position; // left top corner
    Vec2 size;

public:
    Sprite(BitmapNames bitmapName, Vec2 position, Vec2 size)
        : bitmapName(bitmapName), position(position), size(size / SCALE_DIV) {}

    void move(Vec2 delta) {
        position = position + delta;
    }

    Vec2 getCenter() const {
        return position + (size / 2);
    }

    int getMeanSize() const {
        return (size.x + size.y) / 2;
    }

    BitmapNames getBitmapName() const {
        return bitmapName;
    }

    D2D_RECT_F getD2D_RECT_F() const {
        return D2D1::RectF(position.x, position.y, position.x + size.x, position.y + size.y);
    }

    bool outOfScreen(Vec2 screenSize) const {
        return position.x + size.x < 0 ||
               position.y + size.y < 0 ||
               position.x > screenSize.x ||
               position.y > screenSize.y;
    }
};


#endif //ASTEROID_DESTROYER_SPRITE_H
