#include "Player.h"

#include "Engine.h"
#include "Input.h"
#include "Movable.h"
#include "Timer.h"
#include "Vec2.h"
#include "BitmapsManager.h"
#include "BitmapNames.h"

Player::Player(Vec2 position, int colliderRadius, int lives, Engine &engine)
        : Movable(position, colliderRadius, BitmapNames::PLAYER),
          lives(lives), score(0), immune(false), spawnPosition(position), engine(engine) {}

void Player::handleInput() {
    velocity = Vec2(0, 0);

    for (auto input : InputSingleton::getInstance().inputs) {
        switch (input) {
            case Input::MOVE_UP:
                velocity.y = -1;
                break;
            case Input::MOVE_DOWN:
                velocity.y = 1;
                break;
            case Input::MOVE_LEFT:
                velocity.x = -1;
                break;
            case Input::MOVE_RIGHT:
                velocity.x = 1;
                break;
            case Input::SHOOT:
                shoot();
                break;
            default:
                break;
        }
    }

    InputSingleton::getInstance().inputs.clear();
}

void Player::update() {
    handleInput();
    Movable::update();
}

void Player::addScore(int s) {
    score += s;
}

void Player::die() {
    lives -= 1;
    if (lives > 0) {
        respawn();
    } else {
        engine.gameOver();
    }
}

bool Player::isImmune() const {
    return immune;
}

void Player::shoot() {
    auto bullets = engine.getBullets();
    bullets.emplace_back(Vec2(position.x + 30, position.y - 30), Vec2(0, -1), BitmapNames::BULLET);
    bullets.emplace_back(Vec2(position.x - 30, position.y - 30), Vec2(0, -1), BitmapNames::BULLET);
}

void Player::respawn() {
    immune = true;
    Timer::setTimeout([this]() {
        immune = false;
    }, 3000);
    position = spawnPosition;
}