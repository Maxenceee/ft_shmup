#include "collision_box.hpp"

CollisionBox::CollisionBox(): width(0), height(0)
{
}

CollisionBox::CollisionBox(int width, int height)
{
	this->width = width;
	this->height = height;
}

CollisionBox::~CollisionBox()
{
}

int	CollisionBox::getWidth()
{
	return (this->width);
}

int	CollisionBox::getHeight()
{
	return (this->height);
}
