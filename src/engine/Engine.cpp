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

Engine::Engine() : startTime(std::chrono::system_clock::now()),
        lastUpdateTime(std::chrono::system_clock::now()),
        deltaTime{constants::US_PER_FRAME},
        player(std::make_unique<Player>(constants::START_LIVES, *this)) {}

std::vector<Bullet> &Engine::getBullets() {
    return bullets;
}

void Engine::update() {
    if (isGameOver()) {
        if (canCloseWindow && Singleton<Input>::getInstance().isKeyPressed(Key::SPACE)) {
            Singleton<MainWindow>::getInstance().CloseWindow();
        }

        return;
    }

    calcDeltaTime();

    // this resolves weird bug with window scaling
    clearCanary();

    // scale update
    for (auto &asteroidDebris : asteroidsDebris) {
        asteroidDebris.update();
    }
    for (auto &explosion : explosions) {
        explosion.update();
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

    // remove invisible explosions
    for (auto &explosion : explosions) {
        if (explosion.isFinished()) {
            explosion = explosions.back();
            explosions.pop_back();
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

    // this resolves weird bug with window scaling
    setCanary();

    // should be called at the end of each physics update
    Singleton<Input>::getInstance().update();
}

void Engine::gameOver() {
    gameOver_ = true;
    Timer::setTimeout([this]() {
        canCloseWindow = true;
    }, constants::CLOSE_WINDOW_DELAY);
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
    for (auto &explosion : explosions) {
        explosion.Draw();
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
                explode(bullets[j].getCollider().getCollisionPoint(asteroids[i].getCollider()));
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
            explode(player->getCollider().getPosition(), constants::PLAYER_EXPLOSION_SCALE);
            player->die();
        }
    }
}

utils::duration Engine::getTimeSinceStart() const {
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

bool Engine::getCanCloseWindow() const {
    return canCloseWindow;
}

void Engine::setCanary() {
    asteroidsDebris.emplace_back(Vec2(), BitmapNames::ASTEROID1, 1.0f, 0);
}

void Engine::clearCanary() {
    if (!asteroidsDebris.empty()) {
        asteroidsDebris.pop_back();
    }
}

void Engine::explode(Vec2 position, float scale) {
    explosions.emplace_back(position, scale);
}
