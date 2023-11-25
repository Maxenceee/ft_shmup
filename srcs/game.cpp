#include "game.hpp"
#include <algorithm>

Game::Game()
{
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