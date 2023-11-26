#include "enemy.hpp"
#include "sprite.hpp"

class BossBullet : public Enemy
{
private:
	std::string		spritebuff;
	Sprite			sprite = Sprite(Position(0, 0), &spritebuff);

public:
	BossBullet(Position position, Game *game, std::string buff);
	~BossBullet();

	void update();
	void draw();
};
