#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <filesystem>
#include "collision_box.hpp"
#include "position.hpp"
#include "read_file.hpp"
#include "rock.hpp"

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
	std::vector<Rock *>		rocks;

	std::vector<std::string>	sprites;

	bool	parse_rocks(std::string path);

public:
	World(Game *game, Position pos, CollisionBox bounds);
	~World();

	bool	init();
	void	draw();
	void	update();
};
