#pragma once
#include "enemy.hpp"

class HatcherEnemy : public Enemy
{
public:
	HatcherEnemy();
	HatcherEnemy(Position position, Game *game, int health);
	~HatcherEnemy();

	void update() override;
	void draw() override;
};
