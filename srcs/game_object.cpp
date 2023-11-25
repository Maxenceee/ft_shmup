#include "game_object.hpp"

GameObject::GameObject()
{
    this->position = Position(0, 0);
}

GameObject::GameObject(Position position, CollisionBox bounding_box)
{
    this->position = position;
}
GameObject::~GameObject()
{
}

bool    GameObject::collidesWith(GameObject *other)
{
    if ((this->getPosition().getX() - 1 >= other->getPosition().getX()
        && this->getPosition().getX() + 1 <= other->getPosition().getX())
        && this->getPosition().getY() == other->getPosition().getY())
        return (true);
    return (false);
}

Position& GameObject::getPosition()
{
    return (this->position);
}

CollisionBox& GameObject::getBounds()
{
    return (this->bounding_box);
}
