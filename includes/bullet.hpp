#ifndef BULLET_HPP
# define BULLET_HPP
# include "game.hpp"
# include "gameobject.hpp"

class Bullet : public GameObject
{
private:
    int damage;
public:
    Bullet();
    Bullet(Position position, int damage);
    ~Bullet();

    void update(Game *game) override;
    void draw() override;
    bool shouldDelete() override;

    int getDamage() const;
};
#endif