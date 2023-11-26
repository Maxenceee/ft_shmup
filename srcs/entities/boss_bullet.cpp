#include "boss_bullet.hpp"
#include "game.hpp"
#include "../srcs/utils/read_file.hpp"

BossBullet::BossBullet(Position position, Game *game, std::string buff) : Enemy(position, CollisionBox(8, 4), game, 600, 600)
{
	this->reset_shootcooldown = 0;
	this->shootcooldown = 0;
	this->spritebuff = buff;
	this->sprite = Sprite(this->position, &this->spritebuff);
}

BossBullet::~BossBullet()
{
}

void BossBullet::update()
{
	ticks++;
	if (ticks % 24 == 0)
	{
		this->getPosition().setY(this->getPosition().getY() + 1);
	}
	if (ticks % 72 == 0)
	{
		this->shoot(this->game, this->getPosition(), 1, Position(0, 1));
		this->shoot(this->game, this->getPosition(), 1, Position(1, 1));
		this->shoot(this->game, this->getPosition(), 1, Position(-1, 1));
		this->health = 0;
	}
}

void BossBullet::draw()
{
	BossBullet::sprite.getPosition()->setX(this->getPosition().getX() + this->getGame()->getOffset().getX());
	BossBullet::sprite.getPosition()->setY(this->getPosition().getY() + this->getGame()->getOffset().getY());
	BossBullet::sprite.draw();
}
