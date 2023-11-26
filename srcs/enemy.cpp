#include "enemy.hpp"
#include "bullet.hpp"
#include <ncurses.h>

Enemy::Enemy()
{
    this->health = 1;
    this->killreward = 0;
}
Enemy::Enemy(Position position, CollisionBox bounding_box, Game *game, int health, int reward) : Shooter(position, bounding_box, game, health, 0, ObjectTeam::ENEMY)
{
    this->health = health;
    this->killreward = reward;
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
    Shooter::update();
    this->ticks++;
    if (ticks % 15 == 0)
        this->getPosition().setY(this->getPosition().getY() + 1);
    
    if (ticks % 30 == 0)
        this->getPosition().setX(this->getPosition().getX() + rand() % 3 - 1);

    if (ticks % 40 == 0)
    {
        Position bullet_pos = this->getPosition();
        bullet_pos.setY(bullet_pos.getY() + 1);
        this->shoot(this->getGame(), bullet_pos, 1, Position(0, 1));
    }
}

void Enemy::draw()
{
    if (this->getPosition().getX() < 1 || this->getPosition().getX() >= this->getGame()->getBounds().getWidth())
        return;
    if (this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
        return;
    int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
    int y = this->getPosition().getY() + this->getGame()->getOffset().getY();
    mvprintw(y, x, "👾");
}

bool Enemy::shouldDelete()
{
    return (this->health <= 0 || this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 2);
}