#include "game.hpp"
#include <algorithm>

Game::Game(CollisionBox bounding_box, uint32_t nb_player)
{
	this->bounding_box = bounding_box;
	// this->offset_y = nb_player;
	this->world = new World(this, this->offset, bounding_box);
	if (!this->world->init())
		this->exit = true;
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
	this->score += SCORE_MULTIPLIER;

	auto it = this->objects.begin();
	while (it != this->objects.end())
	{
		if ((*it)->shouldDelete())
		{
			delete *it;
			it = this->objects.erase(it);
		}
		else
		{
			(*it)->update();
			++it;
		}
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
	mvprintw(LINES - 1, 2, "Score: %d", this->score);
}

void Game::Tick()
{
	this->world->update();
	this->Update();
	this->Draw();
}

void	Game::addScore(int score)
{
	this->score += score;
}

void	Game::setExitMessage(std::string message)
{
	this->exit_message = message;
}

void	Game::printExit()
{
	std::cerr << this->exit_message << std::endl;
}
