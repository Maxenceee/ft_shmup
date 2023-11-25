#pragma once

#include "position.hpp"
#include "collision_box.hpp"

class Game;

class GameObject
{
private:
    CollisionBox	bounding_box;
    Position        position;

public:
    GameObject();
    GameObject(Position position, CollisionBox bounding_box);
    virtual ~GameObject();

    virtual void    update(Game *game) = 0;
    virtual void    draw() = 0;

    virtual bool    shouldDelete() = 0;
    Position&       getPosition();
    CollisionBox&   getBounds();
    bool collidesWith(GameObject *other);
};

