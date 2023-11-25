#include "game_object.hpp"

GameObject::GameObject()
{
	this->position = Position(0, 0);
	this->game = nullptr;
}

GameObject::GameObject(Position position, CollisionBox bounding_box, Game *game)
{
	this->position = position;
	this->game = game;
}
GameObject::~GameObject()
{
}

bool    GameObject::isEnemy()
{
	return (false);
}

bool    GameObject::collidesWith(GameObject *other)
{
	if (this->getPosition().getX() == other->getPosition().getX()
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

Game *GameObject::getGame() const
{
	return (this->game);
}
