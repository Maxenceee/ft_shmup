#pragma once

#include "collision_box.hpp"
#include "position.hpp"

class Rock
{
private:
	Position		position;
	CollisionBox	bounds;
	std::string		*buff;

public:
	Rock(Position pos, std::string *buff);
	~Rock();

	void	draw();
};
