#ifndef ASTEROID_DESTROYER_ASTEROID_H
#define ASTEROID_DESTROYER_ASTEROID_H


#include "GameObject.h"
#include "Vec2.h"
#include "BitmapNames.h"

#include <d2d1.h>

class Asteroid : public GameObject {
public:
    Asteroid(Vec2 position, Vec2 velocity, BitmapNames bitmapName);

    void Draw(ID2D1HwndRenderTarget *pTarget) override;

private:
    float calcAngle() const;
};


#endif //ASTEROID_DESTROYER_ASTEROID_H
