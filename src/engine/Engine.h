#ifndef ASTEROID_DESTROYER_ENGINE_H
#define ASTEROID_DESTROYER_ENGINE_H


#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "AsteroidsSpawnDelayer.h"
#include "AsteroidDebris.h"

#include <chrono>
#include <memory>
#include <vector>

class Player;

class Engine {
public:
    using time_point = std::chrono::system_clock::time_point;
    using duration = std::chrono::system_clock::duration;

private:
    time_point startTime;
    time_point lastTime;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
    std::unique_ptr<Player> player;
    AsteroidsSpawnDelayer asteroidsSpawnDelayer;
    std::vector<AsteroidDebris> asteroidsDebris;

public:
    Engine();

    std::vector<Bullet> &getBullets();

    // Spawns player. Should be called after window is created
    void start();

    // Updates the game state, should be called once per frame
    void update();

    // Holds the thread for a certain amount of time to keep the FPS constant
    void wait();

    void gameOver();

    void DrawGameObjects(ID2D1HwndRenderTarget *pTarget);

    duration getTimeSinceStart() const;

    std::wstring getText() const;

private:
    void checkCollisions();

    void makeDebris(const Asteroid &asteroid);
};


#endif //ASTEROID_DESTROYER_ENGINE_H
