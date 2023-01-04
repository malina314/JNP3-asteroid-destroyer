#include "Player.h"

#include "Engine.h"
#include "Input.h"
#include "GameObject.h"
#include "Timer.h"
#include "Vec2.h"
#include "BitmapNames.h"
#include "MainWindow.h"
#include "common/constants.h"

Player::Player(int lives, Engine &engine)
        : GameObject(BitmapNames::PLAYER), lives(lives), score(0), immune(false), engine(engine) {}

void Player::handleInput() {
    velocity = Vec2(0, 0);

    Input &input = Singleton<Input>::getInstance();

    if (input.isKeyPressed(Key::UP)) {
        velocity += Vec2(0, -constants::PLAYER_SPEED);
    }
    if (input.isKeyPressed(Key::DOWN)) {
        velocity += Vec2(0, constants::PLAYER_SPEED);
    }
    if (input.isKeyPressed(Key::LEFT)) {
        velocity += Vec2(-constants::PLAYER_SPEED, 0);
    }
    if (input.isKeyPressed(Key::RIGHT)) {
        velocity += Vec2(constants::PLAYER_SPEED, 0);
    }

    if (input.isKeyDown(Key::SPACE)) {
        shoot();
    }
}

void Player::update() {
    handleInput();
    GameObject::update();
}

void Player::addScore(int s) {
    score += s;
}

void Player::die() {
    lives--;
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
    // left
    bullets.emplace_back(Vec2(center.x + constants::LEFT_BULLET_OFFSET_X,center.y + constants::BULLET_OFFSET_Y),
                         Vec2(0, constants::BULLET_SPEED),
                         BitmapNames::BULLET);
    // right
    bullets.emplace_back(Vec2(center.x + constants::RIGHT_BULLET_OFFSET_X,center.y + constants::BULLET_OFFSET_Y),
                         Vec2(0, constants::BULLET_SPEED),
                         BitmapNames::BULLET);
}

void Player::respawn() {
    immune = true;
    Timer::setTimeout([this]() {
        immune = false;
    }, constants::IMMUNE_TIME_MS);
    spawn();
}

void Player::spawn() {
    Vec2 windowSize = Singleton<MainWindow>::getInstance().GetWindowSize();
    Vec2 target = Vec2(windowSize.x / 2, windowSize.y + constants::PLAYER_SPAWN_OFFSET);
    Vec2 delta = target - collider.getPosition();

    move(delta);
}

int Player::getLives() const {
    return lives;
}

int Player::getScore() const {
    return score;
}

void Player::Draw(ID2D1HwndRenderTarget *pTarget) {
    float opacity = isImmune() ? 0.5f : 1.0f;
    Singleton<BitmapsManager>::getInstance().Draw(pTarget, sprite.getBitmapName(), sprite.getD2D_RECT_F(), opacity);
}
