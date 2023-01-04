#include "Engine.h"

#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Vec2.h"
#include "AsteroidsSpawnDelayer.h"
#include "common/utils.h"
#include "common/constants.h"
#include "common/Singleton.h"
#include "BitmapsManager.h"
#include "MainWindow.h"
#include "Input.h"

#include <chrono>
#include <memory>
#include <thread>
#include <vector>
#include <string>

#include <iostream> // todo: remove

Engine::Engine() : startTime(std::chrono::system_clock::now()),
        lastUpdateTime(std::chrono::system_clock::now()),
        deltaTime{constants::US_PER_FRAME},
        player(std::make_unique<Player>(constants::START_LIVES, *this)) {}

std::vector<Bullet> &Engine::getBullets() {
    return bullets;
}

void Engine::update() {
    if (isGameOver()) {
        return;
    }

    calcDeltaTime();

    // scale update
    for (auto &asteroidDebris : asteroidsDebris) {
        asteroidDebris.update();
    }

    // position update
     for (auto &asteroid : asteroids) {
        asteroid.update(deltaTime.count());
    }
    for (auto &bullet : bullets) {
        bullet.update(deltaTime.count());
    }

    // position update & handle input
    player->update(deltaTime.count());

    // check collisions
    checkCollisions();

    Vec2 screenSize = Singleton<MainWindow>::getInstance().GetWindowSize();

    // remove invisible debris
    for (auto &asteroidDebris : asteroidsDebris) {
        if (!asteroidDebris.visible()) {
            asteroidDebris = asteroidsDebris.back();
            asteroidsDebris.pop_back();
        }
    }

    // remove bullets that are out of bounds
    for (auto &bullet : bullets) {
        if (bullet.outOfScreen(screenSize)) {
            bullet = bullets.back();
            bullets.pop_back();
        }
    }

    // remove asteroids that are out of bounds
    for (auto &asteroid : asteroids) {
        if (asteroid.outOfScreen(screenSize)) {
            asteroid = asteroids.back();
            asteroids.pop_back();
        }
    }

    // spawn asteroids
    if (asteroids.size() < constants::MAX_ASTEROIDS_COUNT) {
        if (asteroidsSpawnDelayer.canSpawn()) {
            asteroids.emplace_back(
                    Vec2(utils::random(constants::ASTEROIDS_SPAWN_MARGIN,
                                       screenSize.x - constants::ASTEROIDS_SPAWN_MARGIN),
                         constants::ASTEROIDS_SPAWN_OFFSET_TOP),
                    Vec2(0, constants::ASTEROIDS_SPEED),
                    BitmapsManager::randomAsteroid());
            asteroidsSpawnDelayer.lock();
        }
    }

    Singleton<Input>::getInstance().update();
}

void Engine::gameOver() {
    gameOver_ = true;
}

void Engine::DrawGameObjects(ID2D1HwndRenderTarget *pTarget) {
    for (auto &asteroidDebris : asteroidsDebris) {
        asteroidDebris.Draw(pTarget);
    }
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
    for (size_t i = 0; i < asteroids.size(); ++i) {
        for (size_t j = 0; j < bullets.size(); ++j) {
            if (bullets[j].getCollider().collidesWith(asteroids[i].getCollider())) {
                player->addScore(constants::SCORE_PER_ASTEROID);
                makeDebris(asteroids[i]);
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
    for (size_t i = 0; i < asteroids.size(); ++i) {
        if (!player->isImmune() && asteroids[i].getCollider().collidesWith(player->getCollider())) {
            player->die();
        }
    }
}

Engine::duration Engine::getTimeSinceStart() const {
    return std::chrono::system_clock::now() - startTime;
}

std::wstring Engine::getText() const {
    return L"Score: " + std::to_wstring(player->getScore()) + L"\nLives: " +
           std::to_wstring(player->getLives());
}

std::wstring Engine::getGameOverText() const {
    return L"GAME OVER!\nScore: " + std::to_wstring(player->getScore());
}

void Engine::makeDebris(const Asteroid &asteroid) {
    asteroidsDebris.emplace_back(asteroid.getSprite().getPosition(),
                                 BitmapsManager::randomAsteroid(), 1.0f);
}

bool Engine::isGameOver() const {
    return gameOver_;
}

void Engine::calcDeltaTime() {
    auto now = std::chrono::system_clock::now();
    deltaTime = now - lastUpdateTime;
    lastUpdateTime = now;
}
