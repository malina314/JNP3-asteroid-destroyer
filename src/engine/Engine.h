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

    void DrawGameObjects(std::function<void(BitmapNames, D2D_RECT_F)> &drawFunction) {
        player->Draw(drawFunction);
        for (auto &asteroid : asteroids) {
            asteroid.Draw(drawFunction);
        }
        for (auto &bullet : bullets) {
            bullet.Draw(drawFunction);
        }
    }

    static void sDrawGameObjects(Engine &engine, std::function<void(BitmapNames, D2D_RECT_F)> drawFunction) {
        engine.player->Draw(drawFunction);
        for (auto &asteroid: engine.asteroids) {
            asteroid.Draw(drawFunction);
        }
        for (auto &bullet: engine.bullets) {
            bullet.Draw(drawFunction);
        }
    }
};


#endif //ASTEROID_DESTROYER_ENGINE_H
