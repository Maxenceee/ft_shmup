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
    // this->objects.erase(std::remove_if(this->objects.begin(), this->objects.end(), [] (GameObject *obj) {
    //     if (obj->shouldDelete())
    //     {
    //         delete (obj);
    //         return (true);
    //     }
    //     return (false);
    // }));
    auto iter = this->objects.begin();
    while (iter != this->objects.end())
    {
        if ((*iter)->shouldDelete())
        {
            delete (*iter);
            iter = this->objects.erase(iter);
        }
        else
            (*iter++)->update(this);
    }
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