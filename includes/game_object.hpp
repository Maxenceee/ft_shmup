#pragma once

#include "position.hpp"
#include "collision_box.hpp"

class Game;

enum class ObjectTeam
{
    PLAYER,
    ENEMY,
};

class GameObject
{
protected:
    CollisionBox    bounding_box;
    Position        position;
    Game            *game;
    ObjectTeam      team = ObjectTeam::ENEMY;

public:
    GameObject();
    GameObject(Position position, CollisionBox bounding_box, Game *game);
    virtual ~GameObject();

    virtual void    update() = 0;
    virtual void    draw() = 0;

    virtual bool    shouldDelete() = 0;
    virtual bool isShooter();

    ObjectTeam      getTeam() const;
    bool collidesWith(GameObject *other);
    Position&       getPosition();
    CollisionBox&   getBounds();
    Game *getGame() const;
};

