#include "game.hpp"
#include "colors.hpp"
#include <algorithm>
#include "enemy.hpp"

Game::Game(CollisionBox bounding_box, Position pos, uint32_t nb_player)
{
	this->bounding_box = bounding_box;
    this->offset = pos;
    this->player = new Player(Position(bounding_box.getWidth() / 2, bounding_box.getHeight() - 3), this, 10);
    this->addObject(player);
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
	spawnEnemies();
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
    attron(COLOR_PAIR(HEARTS_PAIR));
    for (int i = 0; i < this->player->getHealth(); i++)
    {
        mvprintw(LINES - 1, COLS / 2 - 1 + i, "❤️");
    }
    attroff(COLOR_PAIR(HEARTS_PAIR));
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
