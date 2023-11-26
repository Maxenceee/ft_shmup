#include "position.hpp"

Position::Position()
{
	this->x = 0;
	this->y = 0;
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

int		Position::getX() const
{
	return (this->x);
}

int		Position::getY() const
{
	return (this->y);
}

void	Position::setX(int x)
{
	this->x = x;
}

void	Position::setY(int y)
{
	this->y = y;
}
