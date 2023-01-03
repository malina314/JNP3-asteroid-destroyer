#include "Player.h"

#include "Engine.h"
#include "Input.h"
#include "GameObject.h"
#include "Timer.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "MainWindow.h"

namespace {
    constexpr int PLAYER_SPEED = 10;
}

Player::Player(int lives, Engine &engine)
        : GameObject(BitmapNames::PLAYER), lives(lives), score(0), immune(false), engine(engine) {}

void Player::handleInput() {
    velocity = Vec2(0, 0);
    LOG();

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

    LOG();
    Singleton<Input>::getInstance().inputs.clear();
}

void Player::update() {
    handleInput();
    GameObject::update();
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
    Vec2 center = sprite.getCenter();
    bullets.emplace_back(Vec2(center.x - 23, center.y - 40), Vec2(0, -1), BitmapNames::BULLET); // left
    bullets.emplace_back(Vec2(center.x + 13, center.y - 40), Vec2(0, -1), BitmapNames::BULLET); // right
}

void Player::respawn() {
    LOG();
    immune = true;
    Timer::setTimeout([this]() {
        immune = false;
    }, 3000);
    spawn();
}

void Player::spawn() {
    Vec2 windowSize = Singleton<MainWindow>::getInstance().GetWindowSize();
    Vec2 target = Vec2(windowSize.x / 2, windowSize.y - 75);
    Vec2 delta = target - collider.getPosition();

    move(delta);
}
