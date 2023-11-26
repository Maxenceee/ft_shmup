#pragma once

#include "game.hpp"
#include "game_object.hpp"

class Bullet : public GameObject
{
private:
    int damage;
    Position direction;
public:
    Bullet();
    Bullet(Position position, Game *game, int damage, ObjectTeam team, Position dir = Position(0, 1));
    ~Bullet();

    void update() override;
    void draw() override;
    bool shouldDelete() override;

    void checkCollision();

    int getDamage() const;
};
