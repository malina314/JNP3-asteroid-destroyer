#include "Engine.h"

#include "Asteroid.h"
#include "Bullet.h"
#include "Input.h"
#include "Movable.h"
#include "Player.h"
#include "Vec2.h"
#include "common/utils.h"
#include "BitmapsManager.h"

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#include <iostream> // todo: remove

namespace {
    constexpr uint64_t FPS = 60;
    constexpr uint64_t NS_PER_FRAME = 1'000'000'000 / FPS;
}

Engine::Engine() : lastTime(std::chrono::system_clock::now()),
           player(std::make_unique<Player>(70, 3, *this)) {}

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

    // collision detection
    for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();) {
        // collision with bullet
        for (auto &bullet : bullets) {
            if (bullet.collider.collidesWith(asteroidIt->collider)) {
                player->addScore(1);
                asteroidIt = asteroids.erase(asteroidIt);
                continue;
            }
        }
        // collision with player
        if (!player->isImmune() && asteroidIt->collider.collidesWith(player->collider)) {
            player->die();
        }
        ++asteroidIt;
    }

    // remove bullets that are out of bounds
    // todo: test if this works
    for (auto &bullet : bullets) {
        if (bullet.position.outOfScreen()) {
            bullet = bullets.back();
            bullets.pop_back();
        }
    }

    // remove asteroids that are out of bounds
    // todo: test if this works
    for (auto &asteroid : asteroids) {
        if (asteroid.position.outOfScreen()) {
            asteroid = asteroids.back();
            asteroids.pop_back();
        }
    }

    // spawn asteroids
    if (asteroids.size() < 10) {
        asteroids.emplace_back(Vec2(utils::random(200, 1720), -200), Vec2(0, 1), BitmapsManager::randomAsteroid());
    }
}

// Holds the thread for a certain amount of time to keep the FPS constant
void Engine::wait() {
    // todo: improve this
    std::this_thread::sleep_for(std::chrono::nanoseconds(NS_PER_FRAME));

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
