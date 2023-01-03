#include "Player.h"

#include "Engine.h"
#include "Input.h"
#include "Movable.h"
#include "Timer.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "MainWindow.h"

namespace {
    constexpr int PLAYER_SPEED = 10;
}

Player::Player(int colliderRadius, int lives, Engine &engine)
        : Movable(Vec2(0, 0), colliderRadius, BitmapNames::PLAYER),
          lives(lives), score(0), immune(false), engine(engine) {}

void Player::handleInput() {
    velocity = Vec2(0, 0);

    for (auto input : Singleton<Input>::getInstance().inputs) {
        switch (input) {
            case Input_t::MOVE_UP:
                velocity.y = -PLAYER_SPEED;
                break;
            case Input_t::MOVE_DOWN:
                velocity.y = PLAYER_SPEED;
                break;
            case Input_t::MOVE_LEFT:
                velocity.x = -PLAYER_SPEED;
                break;
            case Input_t::MOVE_RIGHT:
                velocity.x = PLAYER_SPEED;
                break;
            case Input_t::SHOOT:
                shoot();
                break;
            default:
                break;
        }
    }

    Singleton<Input>::getInstance().inputs.clear();
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
    auto &bullets = engine.getBullets();
    bullets.emplace_back(Vec2(position.x + 30, position.y - 30), Vec2(0, -1), BitmapNames::BULLET);
    bullets.emplace_back(Vec2(position.x - 30, position.y - 30), Vec2(0, -1), BitmapNames::BULLET);
}

void Player::respawn() {
    immune = true;
    Timer::setTimeout([this]() {
        immune = false;
    }, 3000);
    spawn();
}

void Player::spawn() {
    Vec2 pos = Singleton<MainWindow>::getInstance().GetWindowSize();
    position = Vec2(pos.x / 2, pos.y - 75);
}
