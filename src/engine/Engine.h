#ifndef ASTEROID_DESTROYER_ENGINE_H
#define ASTEROID_DESTROYER_ENGINE_H


#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "AsteroidsSpawnDelayer.h"
#include "AsteroidDebris.h"
#include "common/utils.h"
#include "Explosion.h"

#include <memory>
#include <vector>

class Player;

class Engine {
    utils::time_point startTime;
    utils::time_point lastUpdateTime;
    utils::duration deltaTime;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
    std::unique_ptr<Player> player;
    AsteroidsSpawnDelayer asteroidsSpawnDelayer;
    std::vector<AsteroidDebris> asteroidsDebris;
    bool gameOver_;
    bool canCloseWindow;
    std::vector<Explosion> explosions;

public:
    Engine();

    std::vector<Bullet> &getBullets();

    // Spawns player. Should be called after window is created
    void start();

    // Updates the game state, should be called once per frame
    void update();

    // Sets the game over state
    void gameOver();

    bool isGameOver() const;

    void DrawGameObjects(ID2D1HwndRenderTarget *pTarget);

    utils::duration getTimeSinceStart() const;

    std::wstring getText() const;

    std::wstring getGameOverText() const;

    bool getCanCloseWindow() const;

private:
    void checkCollisions();

    void makeDebris(const Asteroid &asteroid);

    // Calculates the time passed since last update
    void calcDeltaTime();

    // Should be called at the end of update
    void setCanary();

    // Should be called at the beginning of update
    void clearCanary();

    void explode(Vec2 position, float scale = 1.0f);
};


#endif //ASTEROID_DESTROYER_ENGINE_H
