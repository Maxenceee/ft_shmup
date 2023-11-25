#pragma once

#include "game.hpp"
#include "game_object.hpp"

class Bullet : public GameObject
{
private:
    int damage;
    int direction;
public:
    Bullet();
    Bullet(Position position, Game *game, int damage, int dir = 1);
    ~Bullet();

    void update() override;
    void draw() override;
    bool shouldDelete() override;

    int getDamage() const;
};
