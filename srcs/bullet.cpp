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
	mvprintw(this->getPosition().getY(), this->getPosition().getX(), "|");
}

bool Bullet::shouldDelete()
{
	if (this->damage <= 0)
		return (true);
	if (this->getPosition().getY() >= LINES)
		return (true);
	return (false);
}
