#include "sprite.hpp"

Sprite::Sprite(Position pos, std::string *buff): position(pos), buff(buff)
{
}

Sprite::~Sprite()
{
}

void	Sprite::draw()
{
	int	y = this->position.getY();
	int	x = this->position.getX();

	for (auto i : *this->buff)
	{
		// dprintf(2, "c %c x=%d y=%d\n", i, x, y);
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

Position	*Sprite::getPosition()
{
	return (&this->position);
}
