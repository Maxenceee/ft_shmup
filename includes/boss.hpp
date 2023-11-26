#pragma once

#include <iostream>
#include "position.hpp"
#include "shooter.hpp"

class Boss : public Shooter
{
private:
	int			damage;
	std::string	buff;
	Position	move_to;
	bool		is_moving = false;
	int			tick;

public:
	Boss(Game *game, std::string boss_buff, int damages, int life);
	~Boss();

	void	update();
	void	draw();
	void	move();
};
