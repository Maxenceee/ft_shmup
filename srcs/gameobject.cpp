#include "gameobject.hpp"

GameObject::GameObject()
{
    this->position = Position(0, 0);
}

GameObject::GameObject(Position position)
{
    this->position = position;
}
GameObject::~GameObject()
{
}

Position& GameObject::getPosition()
{
    return (this->position);
}
