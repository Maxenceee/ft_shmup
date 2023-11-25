#include "game_object.hpp"

class Enemy : public GameObject
{
private:
    uint64_t ticks = 0;
    uint64_t reward;
public:
    int health;

    Enemy();
    Enemy(Position position, CollisionBox bounding_box, Game *game, int health, int reward);
    ~Enemy();

    void update() override;
    void draw() override;
    bool shouldDelete() override;
    bool isEnemy() override;
    int getReward() const;

    void shoot(Game *game);
};