#include "bullet.hpp"
#include "game.hpp"
#include "ncurses.h"

Bullet::Bullet()
{
    this->damage = 0;
}

Bullet::Bullet(Position position, int damage) : GameObject(position)
{
    this->damage = damage;
}

Bullet::~Bullet()
{
}

void Bullet::update(Game *game)
{
    this->getPosition().setY(this->getPosition().getY() + 1);
}
void Bullet::draw()
{  
    mvprintw(this->getPosition().getY(), this->getPosition().getX(), "o");
}

bool Bullet::shouldDelete()
{
    if (this->getPosition().getY() >= LINES)
        return (true);
    return (false);
}
