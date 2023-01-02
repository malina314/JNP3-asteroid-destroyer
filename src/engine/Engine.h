#ifndef ASTEROID_DESTROYER_ENGINE_H
#define ASTEROID_DESTROYER_ENGINE_H


#include "Asteroid.h"
#include "Bullet.h"
#include "Input.h"
#include "Movable.h"
#include "Player.h"
#include "Vec2.h"
#include "BitmapNames.h"

#include <chrono>
#include <memory>
#include <vector>

class Player;

class Engine {
    std::chrono::time_point<std::chrono::system_clock> lastTime;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
    std::unique_ptr<Player> player;

public:
    Engine();

    std::vector<Bullet> &getBullets();

    // Updates the game state, should be called once per frame
    void update();

    // Holds the thread for a certain amount of time to keep the FPS constant
    void wait();

    void gameOver();

    void DrawGameObjects(ID2D1HwndRenderTarget *pTarget);
};


#endif //ASTEROID_DESTROYER_ENGINE_H
