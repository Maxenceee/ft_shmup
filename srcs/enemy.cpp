#include "enemy.hpp"
#include "bullet.hpp"
#include <ncurses.h>

Enemy::Enemy()
{
    this->health = 1;
    this->reward = 0;
}
Enemy::Enemy(Position position, CollisionBox bounding_box, Game *game, int health, int reward) : GameObject(position, bounding_box, game)
{
    this->health = health;
    this->reward = reward;
}

Enemy::~Enemy()
{
}

bool Enemy::isEnemy() {
    return (true);
}

void Enemy::update()
{
    this->ticks++;
    if (ticks % 60 == 0)
        this->getPosition().setY(this->getPosition().getY() + 1);
    
    if (ticks % 40 == 0)
        this->getPosition().setX(this->getPosition().getX() + rand() % 3 - 1);
}

void Enemy::draw()
{
    mvprintw(this->getPosition().getY(), this->getPosition().getX(), "👾");
}

bool Enemy::shouldDelete()
{
    return (this->health <= 0 || this->getPosition().getY() >= LINES - 1);
}

int Enemy::getReward() const
{
    return (this->reward);
}

void Enemy::shoot(Game *game)
{
    game->addObject(new Bullet(Position(this->getPosition().getX(), this->getPosition().getY() + 1), game, 1, -1));
}
