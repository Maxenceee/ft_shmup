#include "enemy.hpp"

class DiagonalShootingEnemy : public Enemy
{
public:
	DiagonalShootingEnemy();
	DiagonalShootingEnemy(Position position, Game *game, int health);
	~DiagonalShootingEnemy();

	void update() override;
	void draw() override;
};
