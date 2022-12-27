#ifndef ASTEROID_DESTROYER_PLAYER_H
#define ASTEROID_DESTROYER_PLAYER_H


#include "Engine.h"
#include "Movable.h"
#include "Vec2.h"

class Engine;

class Player : public Movable {
    int lives;
    int score;
    bool immune;
    Vec2 spawnPosition;
    Engine &engine;

public:
    Player(Vec2 position, int colliderRadius, int lives, Engine &engine);

    void update() override;

    void addScore(int s);

    void die();

    bool isImmune() const;

private:
    void handleInput();

    void shoot();

    void respawn();
};


#endif //ASTEROID_DESTROYER_PLAYER_H
