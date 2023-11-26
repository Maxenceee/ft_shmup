#include "enemy_diagonal.hpp"
#include "ncurses.h"
#include "colors.hpp"
#include "game.hpp"

DiagonalEnemy::DiagonalEnemy()
{
}

DiagonalEnemy::DiagonalEnemy(Position position, Game *game, int health, int direction) : Enemy(position, CollisionBox(1,1), game, health, 200)
{
	this->direction = direction;
	this->killreward = 50;
}

DiagonalEnemy::~DiagonalEnemy()
{
}

void DiagonalEnemy::update()
{
	ticks++;
	if (ticks % 2 == 0)
		this->getPosition().setY(this->getPosition().getY() + 1);

	this->getPosition().setX(this->getPosition().getX() + this->direction);

	if (this->getPosition().getX() < 2 || this->getPosition().getX() > this->getGame()->getBounds().getWidth() - 3)
		this->direction *= -1;
}

void DiagonalEnemy::draw()
{
	if (this->getPosition().getX() < 0 || this->getPosition().getX() >= this->getGame()->getBounds().getWidth())
		return ;
	if (this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
		return ;
	int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
	int y = this->getPosition().getY() + this->getGame()->getOffset().getY();
	attron(COLOR_PAIR(ENEMY_BULLET_PAIR));
	mvprintw(y, x, "V");
	attroff(COLOR_PAIR(ENEMY_BULLET_PAIR));
}
