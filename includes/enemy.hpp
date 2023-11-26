#include "shooter.hpp"

class Enemy : public Shooter
{
private:
    uint64_t ticks = 0;
public:

    Enemy();
    Enemy(Position position, CollisionBox bounding_box, Game *game, int health, int reward);
    ~Enemy();

    void    update() override;
    void    draw() override;
    bool    shouldDelete() override;
};