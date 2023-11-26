#include "boss.hpp"
#include "game.hpp"
#include "boss_bullet.hpp"

Position	max_size(std::string buff)
{
	int	max = 0;
	int	x = 0;
	int	y = 0;

	for (int i = 0; i < buff.length(); i++)
	{
		if (buff[i] == '\n')
		{
			x = std::max(max, x);
			max = 0;
			y++;
		}
		max++;
	}
	return (Position(x, y));
}

Boss::Boss(Game *game, std::string boss_buff, int damages, int life): damage(damages), buff(boss_buff)
{
	this->game = game;
	this->position = Position(this->game->getOffset().getX() + (this->game->getBounds().getWidth() / 2), this->game->getOffset().getY() + 1);

	Position	tmp = max_size(boss_buff);
	this->bounding_box = CollisionBox(tmp.getX(), tmp.getY());
	this->game->hasBoss(true);
	this->health = life;
	this->tick = this->game->tick;
}

Boss::~Boss()
{
	this->game->hasBoss(false);
}

void	Boss::update()
{
	this->move();
	if ((this->game->tick - tick) % 60 == 1)
	{
		this->game->addObject(new BossBullet(Position(this->getPosition().getX(), this->getPosition().getY() + this->getBounds().getHeight() / 2 + 1), this->game, this->game->bullet_sprite));
	}
}

void	Boss::draw()
{
	int	y = this->position.getY();
	int	x = this->position.getX();

	for (auto i : this->buff)
	{
		if (i == '\n')
		{
			y++;
			x = this->position.getX();
			continue ;
		}
		if (i != ' ')
		{
			mvprintw(y, x, "%c", i);
		}
		x++;
	}
}

void	Boss::move()
{
	if (!this->is_moving)
	{
		this->move_to = Position(1 + (std::rand() % this->game->getBounds().getWidth()), this->position.getY());
		this->is_moving = true;
	}
	if (this->game->tick % 2)
	{
		int	dist = 1;
		this->position.setX(this->position.getX() + (this->move_to.getX() < this->position.getX() ? -dist : dist));
	}
	if (this->position.getX() == this->move_to.getX())
	{
		this->is_moving = false;
	}
}
