#include "game_object.hpp"

GameObject::GameObject()
{
	this->position = Position(0, 0);
	this->game = nullptr;
}

GameObject::GameObject(Position position, CollisionBox bounding_box, Game *game)
{
	this->bounding_box = bounding_box;
	this->position = position;
	this->game = game;
}

GameObject::~GameObject()
{
}

bool	GameObject::isShooter()
{
	return (false);
}

bool	GameObject::collidesWith(GameObject *other)
{
	return (other->getPosition().getX() <= this->getPosition().getX() && other->getPosition().getX() + other->getBounds().getWidth() > this->getPosition().getX() || other->getPosition().getX() >= this->getPosition().getX() && other->getPosition().getX() < this->getPosition().getX() + this->getBounds().getWidth()) && (other->getPosition().getY() <= this->getPosition().getY() && other->getPosition().getY() + other->getBounds().getHeight() > this->getPosition().getY() || other->getPosition().getY() >= this->getPosition().getY() && other->getPosition().getY() < this->getPosition().getY() + this->getBounds().getHeight());
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

ObjectTeam GameObject::getTeam() const
{
	return (this->team);
}
