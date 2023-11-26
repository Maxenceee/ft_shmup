#include "game.hpp"
#include "colors.hpp"
#include <algorithm>
#include "enemy.hpp"

int get_key()
{
	int input = getch();
	if (input == '\033')
	{
		getch();
		switch (getch())
		{
		case 'A': return (KEY_UP);
		case 'B': return (KEY_DOWN);
		case 'C': return (KEY_RIGHT);
		case 'D': return (KEY_LEFT);
		}
	}
	return (input);
}

Game::Game(CollisionBox bounding_box, Position pos, uint32_t nb_player)
{
	this->bounding_box = bounding_box;
    this->offset = pos;
    this->player = new Player(Position(bounding_box.getWidth() / 2, bounding_box.getHeight() - 3), this, 10);
    this->addObject(player);
    this->world = new World(this, this->offset, bounding_box);
	if (!this->world->init())
		this->exit = true;
	this->home = new Home(this);
}

Game::~Game()
{
	for (auto object : this->objects)
		delete object;
	delete this->world;
	delete this->home;
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
	if (this->home->isActive())
	{
		this->world->renderStars();
		this->home->update();
	}
	else
	{
		this->world->update();
		this->Update();
		this->Draw();
	}
}

void	Game::addScore(int score)
{
	this->score += score;
}

Position& Game::getOffset()
{
    return (this->offset);
}

CollisionBox& Game::getBounds()
{
    return (this->bounding_box);
}

Player* Game::getPlayer() const
{
	return (this->player);
}

void	Game::spawnEnemies()
{
	if (tick++ != 120)
		return;
	tick = 0;
	int nb_enemies = rand() % score / 3000 + 1;
	for (int i = 0; i < nb_enemies; i++)
	{
		int x = rand() % (this->getBounds().getWidth() - 2) + 1;
		int y = 1;
		this->addObject(new Enemy(Position(x, y), CollisionBox(1, 1), this, 1, 10));
	}
}

void	Game::setExitMessage(std::string message)
{
	this->exit_message = message;
}

void	Game::printExit()
{
	std::cerr << this->exit_message << std::endl;
}
