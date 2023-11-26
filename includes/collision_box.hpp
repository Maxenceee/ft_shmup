#pragma once

#include <iostream>

class CollisionBox
{
private:
	int width;
	int height;

public:
	CollisionBox();
	CollisionBox(int width, int height);
	~CollisionBox();

	int	getWidth();
	int	getHeight();
};

