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
    if (ticks % 15 == 0)
        this->getPosition().setY(this->getPosition().getY() + 1);
    
    if (ticks % 30 == 0)
        this->getPosition().setX(this->getPosition().getX() + rand() % 3 - 1);
}

void Enemy::draw()
{
    if (this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
        return;
    int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
    int y = this->getPosition().getY() + this->getGame()->getOffset().getY();
    mvprintw(y, x, "👾");
}

bool Enemy::shouldDelete()
{
    return (this->health <= 0 || this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1);
}

int Enemy::getReward() const
{
    return (this->reward);
}

void Enemy::shoot(Game *game)
{
    game->addObject(new Bullet(Position(this->getPosition().getX(), this->getPosition().getY() + 1), game, 1, -1));
}
