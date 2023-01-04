#ifndef ASTEROID_DESTROYER_CONSTANTS_H
#define ASTEROID_DESTROYER_CONSTANTS_H


#include "Vec2.h"

#include <cstddef>
#include <cstdint>

namespace constants {
    constexpr uint64_t FPS = 60;
    constexpr uint64_t NS_PER_FRAME = 1'000'000'000 / FPS;
    constexpr float NS_PER_FRAME_INV = 1.0f / NS_PER_FRAME;

    constexpr size_t MAX_ASTEROIDS_COUNT = 10;
    constexpr int ASTEROID_RADIUS_MARGIN = 20;
    constexpr int ASTEROIDS_SPAWN_MARGIN = 200;
    constexpr int ASTEROIDS_SPAWN_OFFSET_TOP = -180;
    constexpr int ASTEROID_SPAWN_DELAY_MS = 600;
    constexpr int ASTEROIDS_SPEED = 2;
    constexpr float ASTEROID_ROTATION_SPEED = 100.0f;


    constexpr int PLAYER_SPEED = 4;
    constexpr int PLAYER_SPAWN_OFFSET = -75;
    constexpr int START_LIVES = 3;
    constexpr int SCORE_PER_ASTEROID = 1;
    constexpr int IMMUNE_TIME_MS = 3000;

    constexpr int BULLET_SPEED = -4;
    constexpr int BULLET_OFFSET_Y = -40;
    constexpr int LEFT_BULLET_OFFSET_X = -23;
    constexpr int RIGHT_BULLET_OFFSET_X = 13;

    constexpr int SCALE_DIV = 2;

    constexpr int FIRST_ASTEROID_IN_ENUM = 3;
    constexpr int LAST_ASTEROID_IN_ENUM = 5;

    constexpr float FONT_SIZE = 30.0f;
    constexpr float FONT_SIZE_GAME_OVER = 80.0f;
    constexpr float TEXT_MARGIN_LEFT = 20.0f;
    constexpr float TEXT_MARGIN_TOP = 10.0f;

    constexpr float DEBRIS_DISAPPEARING_SPEED = 0.01f;
    constexpr float DEBRIS_VISIBILITY_THRESHOLD = 0.05f;
    constexpr float DEBRIS_OPACITY = 0.5f;

    const Vec2 BitmapSizes[] = {
            Vec2(142, 150),     // PLAYER
            Vec2(1920, 1080),   // BACKGROUND
            Vec2(20, 20),       // BULLET
            Vec2(400, 400),     // ASTEROID1
            Vec2(400, 400),     // ASTEROID2
            Vec2(400, 400)      // ASTEROID3
    };
} // namespace constants


#endif //ASTEROID_DESTROYER_CONSTANTS_H
