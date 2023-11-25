#include "game.hpp"
#include <algorithm>

Game::Game(CollisionBox bounding_box, uint32_t nb_player)
{
    this->bounding_box = bounding_box;
    this->offset_y = nb_player;
}

Game::~Game()
{
    for (auto object : this->objects)
        delete object;
}

std::vector<GameObject*>& Game::getObjects()
{
    return (this->objects);
}

void Game::Update()
{
    for (auto object : this->objects)
    {
        if (object->shouldDelete())
        {
            this->objects.erase(std::find(this->objects.begin(), this->objects.end(), object));
            delete object;
        }
        else
            object->update(this);
    }
    this->getObjects().insert(this->getObjects().end(), this->objects_to_add.begin(), this->objects_to_add.end());
    this->objects_to_add.clear();
}

void    Game::addObject(GameObject *obj)
{
    this->objects_to_add.push_back(obj);
}

void Game::Draw()
{
    for (auto object : this->objects)
        object->draw();
}

void Game::Tick()
{
    this->Update();
    this->Draw();
}