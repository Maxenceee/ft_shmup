#include "collision_box.hpp"

CollisionBox::CollisionBox(): width(0), height(0)
{
}

CollisionBox::CollisionBox(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
}

CollisionBox::~CollisionBox()
{
}

uint32_t	CollisionBox::getWidth()
{
	return (this->width);
}

uint32_t	CollisionBox::getHeight()
{
	return (this->height);
}