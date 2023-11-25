#include <gameobject.hpp>

class Player : public GameObject
{
private:
	int health;
public:
	Player();
	Player(Position position, int health);
	~Player();

	bool collidesWith(GameObject *other);

	void update(Game *game) override;
	void draw() override;
	bool shouldDelete() override;

	int getHealth() const;
};