#include "enemy_hatcher.hpp"
#include "game.hpp"
#include <ncurses.h>
#include "colors.hpp"

HatcherEnemy::HatcherEnemy()
{
}
HatcherEnemy::HatcherEnemy(Position position, Game *game, int health) : Enemy(position, CollisionBox(1, 1), game, health, 0)
{
	this->killreward = 200;
}

HatcherEnemy::~HatcherEnemy()
{
}

void	HatcherEnemy::update()
{
	ticks++;
	if (ticks % 100 == 0 && this->getPosition().getY() > 2)
	{
		Enemy *enemy = this->game->getRandomEnemy();
		enemy->getPosition().setX(this->getPosition().getX() - 1);
		if (enemy)
			this->getGame()->addObject(enemy);
	}
	else if (ticks % 100 == 0 && this->getPosition().getY() < this->getGame()->getBounds().getHeight() - 2)
	{
		Enemy *enemy = this->game->getRandomEnemy();
		enemy->getPosition().setX(this->getPosition().getX() + 1);
		if (enemy)
			this->getGame()->addObject(enemy);
	}
	if (ticks % 150 == 0)
	{
		this->position.setY(this->position.getY() + 1);
	}
}

void	HatcherEnemy::draw()
{
	if (this->getPosition().getX() < 0 || this->getPosition().getX() >= this->getGame()->getBounds().getWidth())
		return ;
	if (this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
		return ;
	int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
	int y = this->getPosition().getY() + this->getGame()->getOffset().getY();
	attron(COLOR_PAIR(ENEMY_BULLET_PAIR));
	mvprintw(y, x, "H");
	attroff(COLOR_PAIR(ENEMY_BULLET_PAIR));
}
