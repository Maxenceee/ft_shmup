#include "bullet.hpp"
#include "game.hpp"
#include "ncurses.h"

Bullet::Bullet()
{
    this->damage = 0;
}

Bullet::Bullet(Position position, int damage, int dir) : GameObject(position, CollisionBox(1, 1))
{
    this->damage = damage;
    this->direction = dir;
}

Bullet::~Bullet()
{
}

void Bullet::update(Game *game)
{
    this->getPosition().setY(this->getPosition().getY() - this->direction);
}
void Bullet::draw()
{  
    mvprintw(this->getPosition().getY(), this->getPosition().getX(), "|");
}

bool Bullet::shouldDelete()
{
    if (this->getPosition().getY() >= LINES)
        return (true);
    return (false);
}
