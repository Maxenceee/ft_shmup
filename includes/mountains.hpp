#pragma once

#include <iostream>
#include "position.hpp"
#include "collision_box.hpp"
#include <vector>
#include <ncurses.h>

class Mountains
{
private:
	Position		position;
	CollisionBox	bounds;

	std::vector<std::vector<int>>	map;

public:
	Mountains(Position pos, CollisionBox bounds);
	~Mountains();

	void	draw();
};
