#include "bullet.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "ncurses.h"
#include "colors.hpp"

Bullet::Bullet()
{
	this->damage = 0;
}

Bullet::Bullet(Position position, Game *game, int damage, ObjectTeam team, int dir) : GameObject(position, CollisionBox(1, 1), game)
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
	this->getPosition().setY(this->getPosition().getY() + this->direction);
	for (auto &object : this->getGame()->getObjects())
	{
		if (object->isShooter() && object->collidesWith(this))
		{
			Shooter* victim = dynamic_cast<Shooter *>(object);
			this->getGame()->addScore(victim->getKillReward());
			victim->damage(this->damage);
			this->damage = 0;
		}
	}
}

void Bullet::draw()
{
    int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
    int y = this->getPosition().getY() + this->getGame()->getOffset().getY();
    if (this->team == ObjectTeam::ENEMY)
		attron(COLOR_PAIR(ENEMY_BULLET_PAIR));
	mvprintw(y, x, "|");
	if (this->team == ObjectTeam::ENEMY)
		attroff(COLOR_PAIR(ENEMY_BULLET_PAIR));
}

bool Bullet::shouldDelete()
{
    if (this->damage <= 0)
        return (true);
    if (this->direction > 0 && \
        this->getPosition().getY() > this->getGame()->getBounds().getHeight() - this->getGame()->getOffset().getY() - 1)
        return (true);
    else if (this->direction < 0 && \
        this->getPosition().getY() < 2)
        return (true);
    return (false);
}
