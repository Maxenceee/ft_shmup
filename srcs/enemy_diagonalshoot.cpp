#include "enemy_diagonalshoot.hpp"
#include "bullet.hpp"
#include <ncurses.h>
#include "colors.hpp"

DiagonalShootingEnemy::DiagonalShootingEnemy() : Enemy()
{
}

DiagonalShootingEnemy::DiagonalShootingEnemy(Position position, Game *game, int health) : Enemy(position, CollisionBox(1, 1), game, health, 100)
{
}

DiagonalShootingEnemy::~DiagonalShootingEnemy()
{
}

void	DiagonalShootingEnemy::update()
{
	Enemy::update();
	if (ticks % 60 == 0)
	{
		Position pos = this->getPosition();
		pos.setY(pos.getY() + 1);
		this->shoot(this->game, pos, 1, Position(0,1));
		pos.setX(pos.getX() + 1);
		this->shoot(this->game, pos, 1, Position(1,1));
		pos.setX(pos.getX() - 2);
		this->shoot(this->game, pos, 1, Position(-1,1));
	}
}

void	DiagonalShootingEnemy::draw()
{
	if (this->getPosition().getX() < 0 || this->getPosition().getX() >= this->getGame()->getBounds().getWidth())
		return ;
	if (this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
		return ;
	int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
	int y = this->getPosition().getY() + this->getGame()->getOffset().getY();
	attron(COLOR_PAIR(ENEMY_BULLET_PAIR));
	mvprintw(y, x, "W");
	attroff(COLOR_PAIR(ENEMY_BULLET_PAIR));
}
