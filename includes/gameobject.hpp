#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP
# include "position.hpp"

class Game;

class GameObject
{
private:
    Position position;
public:
    GameObject();
    GameObject(Position position);
    virtual ~GameObject();

    virtual void update(Game *game) = 0;
    virtual void draw() = 0;

    virtual bool shouldDelete() = 0;
    Position& getPosition();
};
#endif
