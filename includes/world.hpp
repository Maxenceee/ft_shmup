#pragma once

#include <iostream>
#include "position.hpp"
#include "collision_box.hpp"
#include <vector>
#include <ncurses.h>
#include <filesystem>

namespace fs = std::filesystem;

class Game;

class World
{
private:
	Position		position;
	CollisionBox	bounds;
	uint64_t		ticks;
	int				rock_factor = 1000;
	Game			*game;

	// std::vector<std::vector<int>>	map;
	std::vector<Position*>	stars;
	std::vector<std::pair<Position *, CollisionBox *>>	rocks;

	std::vector<fs::path>	sprites;

	bool	parse_rocks(std::string path);

public:
	World(Game *game, Position pos, CollisionBox bounds);
	~World();

	bool	init();
	void	draw();
	void	update();
};
