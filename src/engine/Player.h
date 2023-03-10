#ifndef ASTEROID_DESTROYER_PLAYER_H
#define ASTEROID_DESTROYER_PLAYER_H


#include "Engine.h"
#include "GameObject.h"
#include "Vec2.h"

class Engine;

class Player : public GameObject {
    int lives;
    int score;
    bool immune;
    Engine &engine;

public:
    Player(int lives, Engine &engine);

    void update(float deltaTime) override;

    void addScore(int s);

    void die();

    bool isImmune() const;

    void spawn();

    int getLives() const;

    int getScore() const;

    void Draw(ID2D1HwndRenderTarget *pTarget) override;

private:
    void handleInput();

    void shoot();

    void respawn();
};


#endif //ASTEROID_DESTROYER_PLAYER_H
