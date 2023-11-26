#include "enemy.hpp"

class DiagonalEnemy : public Enemy
{
private:
	int direction;

public:
	DiagonalEnemy();
	DiagonalEnemy(Position position, Game *game, int health, int direction);
	~DiagonalEnemy();
	void update() override;
	void draw() override;
};
