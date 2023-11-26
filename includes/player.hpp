#pragma once

#include <shooter.hpp>

class Player : public Shooter
{
private:

public:
	Player();
	Player(Position position, Game *game, int health);
	~Player();

	void	update() override;
	void	draw() override;
	bool	shouldDelete() override;
};