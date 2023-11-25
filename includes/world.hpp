#pragma once

#include <iostream>
#include "position.hpp"
#include "collision_box.hpp"
#include <vector>
#include <ncurses.h>

class World
{
private:
	Position		position;
	CollisionBox	bounds;

	std::vector<std::vector<int>>	map;

public:
	World(Position pos, CollisionBox bounds);
	~World();

	void	draw();
};
