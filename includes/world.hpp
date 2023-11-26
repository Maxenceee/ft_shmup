#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <filesystem>
#include "collision_box.hpp"
#include "position.hpp"
#include "../srcs/utils/read_file.hpp"
#include "sprite.hpp"

namespace fs = std::filesystem;

class Game;

class World
{
private:
	Position		position;
	uint64_t		ticks;
	int				Sprite_factor = 1000;
	Game			*game;

	std::vector<Position*>		stars;
	std::vector<Sprite *>		Sprites;

	std::vector<std::string>	sprites;

	bool	parse_Sprites(std::string path);

public:
	World(Game *game, Position pos);
	~World();

	bool	init();
	void	draw();
	void	update();
	void	renderStars();
};
