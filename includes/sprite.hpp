#pragma once

#include <ncurses.h>
#include "collision_box.hpp"
#include "position.hpp"

class Sprite
{
private:
	Position		position;
	CollisionBox	bounds;
	std::string		*buff;

public:
	Sprite(Position pos, std::string *buff);
	~Sprite();

	void		draw();
	Position	*getPosition();
};
