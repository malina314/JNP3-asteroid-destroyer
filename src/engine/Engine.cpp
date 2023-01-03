#include "Engine.h"

#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Vec2.h"
#include "common/utils.h"
#include "common/constants.h"
#include "common/Singleton.h"
#include "BitmapsManager.h"
#include "MainWindow.h"

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#include <iostream> // todo: remove

Engine::Engine() : lastTime(std::chrono::system_clock::now()),
           player(std::make_unique<Player>(constants::START_LIVES, *this)) {}

std::vector<Bullet> &Engine::getBullets() {
    return bullets;
}

void Engine::update() {
    // position update
     for (auto &asteroid : asteroids) {
        asteroid.update();
    }
    for (auto &bullet : bullets) {
        bullet.update();
    }

    // position update & handle input
    player->update();

    // check collisions
    checkCollisions();

    Vec2 screenSize = Singleton<MainWindow>::getInstance().GetWindowSize();

    // remove bullets that are out of bounds
    // todo: test if this works
    for (auto &bullet : bullets) {
        if (bullet.outOfScreen(screenSize)) {
            bullet = bullets.back();
            bullets.pop_back();
        }
    }

    // remove asteroids that are out of bounds
    // todo: test if this works
    for (auto &asteroid : asteroids) {
        if (asteroid.outOfScreen(screenSize)) {
            asteroid = asteroids.back();
            asteroids.pop_back();
        }
    }

    // spawn asteroids
    if (asteroids.size() < constants::MAX_ASTEROIDS_COUNT) {
        asteroids.emplace_back(
                Vec2(utils::random(constants::ASTEROIDS_SPAWN_MARGIN,
                                   screenSize.x - constants::ASTEROIDS_SPAWN_MARGIN),
                     constants::ASTEROIDS_SPAWN_OFFSET_TOP),
                Vec2(0, constants::ASTEROIDS_SPEED),
                BitmapsManager::randomAsteroid());
    }
}

// Holds the thread for a certain amount of time to keep the FPS constant
void Engine::wait() {
    // todo: improve this
    std::this_thread::sleep_for(std::chrono::nanoseconds(constants::NS_PER_FRAME));

//    copilot's code
//    auto now = std::chrono::system_clock::now();
//    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTime).count();
//    if (elapsed < NS_PER_FRAME) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds(NS_PER_FRAME - elapsed));
//    }
//    lastTime = std::chrono::system_clock::now();

//    my code
//    std::chrono::time_point currentTime = std::chrono::system_clock::now();
//    std::chrono::duration deltaTime = currentTime - lastTime;
//    cout << deltaTime.count() << "\n";
//    std::this_thread::sleep_for(std::chrono::nanoseconds(NS_PER_FRAME - deltaTime.count()));
//    lastTime = currentTime;
}

void Engine::gameOver() {
    std::cout << "Game over!" << std::endl;
    exit(2137);
}

void Engine::DrawGameObjects(ID2D1HwndRenderTarget *pTarget) {
    for (auto &asteroid : asteroids) {
        asteroid.Draw(pTarget);
    }
    for (auto &bullet : bullets) {
        bullet.Draw(pTarget);
    }
    player->Draw(pTarget);
}

void Engine::start() {
    player->spawn();
}

void Engine::checkCollisions() {
    // bullets hit asteroids
    for (int i = 0; i < asteroids.size(); ++i) {
        for (int j = 0; j < bullets.size(); ++j) {
            if (bullets[j].getCollider().collidesWith(asteroids[i].getCollider())) {
                player->addScore(constants::SCORE_PER_ASTEROID);
                asteroids[i] = asteroids.back();
                asteroids.pop_back();
                bullets[j] = bullets.back();
                bullets.pop_back();
                --i;
                break;
            }
        }
    }

    // player hit asteroids
    for (int i = 0; i < asteroids.size(); ++i) {
        if (!player->isImmune() && asteroids[i].getCollider().collidesWith(player->getCollider())) {
            player->die();
        }
    }
}
