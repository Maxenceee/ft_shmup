#pragma once

#include <iostream>

class CollisionBox
{
private:
	uint32_t width;
	uint32_t height;

public:
	CollisionBox();
	CollisionBox(uint32_t width, uint32_t height);
	~CollisionBox();

	uint32_t	getWidth();
	uint32_t	getHeight();
};

