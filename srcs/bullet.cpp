#include "bullet.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "ncurses.h"

Bullet::Bullet()
{
	this->damage = 0;
}

Bullet::Bullet(Position position, Game *game, int damage, int dir) : GameObject(position, CollisionBox(1, 1), game)
{
	this->damage = damage;
	this->direction = dir;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	this->getPosition().setY(this->getPosition().getY() - this->direction);
	for (auto &object : this->getGame()->getObjects())
	{
		if (object->isEnemy() && object->collidesWith(this))
		{
			Enemy* enemy = dynamic_cast<Enemy *>(object);
			this->getGame()->addScore(enemy->getReward());
			enemy->health -= this->damage;
			this->damage = 0;
		}
	}
}
void Bullet::draw()
{
    int x = this->getPosition().getX() + this->getGame()->getPosition().getX();
    int y = this->getPosition().getY() + this->getGame()->getPosition().getY();
    mvprintw(y, x, "|");
}

bool Bullet::shouldDelete()
{
    if (this->damage <= 0)
        return (true);
    if (this->direction < 0 && \
        this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
        return (true);
    else if (this->direction > 0 && \
        this->getPosition().getY() < 2)
        return (true);
    return (false);
}
