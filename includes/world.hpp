#pragma once

#include <iostream>
#include "position.hpp"
#include "collision_box.hpp"
#include <vector>
#include <ncurses.h>
#include <filesystem>

namespace fs = std::filesystem;

class World
{
private:
	Position		position;
	CollisionBox	bounds;
	uint64_t		ticks;
	int				rock_factor = 1000;

	// std::vector<std::vector<int>>	map;
	std::vector<Position*>	stars;
	std::vector<std::pair<Position *, CollisionBox *>>	rocks;

	bool	parse_rocks(std::string path);

public:
	World(Position pos, CollisionBox bounds);
	~World();

	void	draw();
	void	update();
};
