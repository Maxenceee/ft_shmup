#include "bullet.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "ncurses.h"
#include "colors.hpp"


Bullet::Bullet()
{
	this->damage = 0;
}

Bullet::Bullet(Position position, Game *game, int damage, ObjectTeam team, Position dir) : GameObject(position, CollisionBox(1, 1), game)
{
	this->damage = damage;
	this->direction = dir;
	this->team = team;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	this->checkCollision();
	this->getPosition().setX(this->getPosition().getX() + this->direction.getX());
	this->getPosition().setY(this->getPosition().getY() + this->direction.getY());
	this->checkCollision();
}

void	Bullet::checkCollision()
{
	for (auto &object : this->getGame()->getObjects())
	{
		if (object->isShooter() && object->collidesWith(this) && object->getTeam() != this->team)
		{
			Shooter* victim = dynamic_cast<Shooter *>(object);
			this->getGame()->addScore(victim->getKillReward());
			victim->damage(this->damage);
			this->damage = 0;
		}
		if (this->getGame()->getHome()->isActive())
			return ;
	}
}

void Bullet::draw()
{
	int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
	int y = this->getPosition().getY() + this->getGame()->getOffset().getY();
	if (this->getPosition().getX() < 0 || this->getPosition().getX() >= this->getGame()->getBounds().getWidth())
		return ;
	if (this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
		return ;
	if (this->team == ObjectTeam::ENEMY)
		attron(COLOR_PAIR(ENEMY_BULLET_PAIR));
	if (direction.getX() == 0)
		mvprintw(y, x, "|");
	else if (direction.getX() == 1)
		mvprintw(y, x, "\\");
	else if (direction.getX() == -1)
		mvprintw(y, x, "/");
	else
		mvprintw(y, x, "|");
	if (this->team == ObjectTeam::ENEMY)
		attroff(COLOR_PAIR(ENEMY_BULLET_PAIR));
}

bool Bullet::shouldDelete()
{
	if (this->damage <= 0)
		return (true);
	if (this->direction.getY() > 0 && \
		this->getPosition().getY() > this->getGame()->getBounds().getHeight() - this->getGame()->getOffset().getY() - 1)
		return (true);
	else if (this->direction.getY() < 0 && \
		this->getPosition().getY() < 2)
		return (true);
	return (false);
}
