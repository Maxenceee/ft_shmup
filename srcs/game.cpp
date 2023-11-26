#include "game.hpp"
#include "colors.hpp"
#include <algorithm>
#include "enemy_diagonal.hpp"
#include "enemy_diagonalshoot.hpp"
#include "enemy_hatcher.hpp"
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

Game::Game(CollisionBox bounding_box, Position pos)
{
	this->bounding_box = bounding_box;
    this->offset = pos;
    this->world = new World(this, this->offset, bounding_box);
	if (!this->world->init())
		this->exit = true;
	begin = std::chrono::steady_clock::now();
	this->home = new Home(this);
}

Game::~Game()
{
	this->stopGame();
	delete this->world;
	delete this->home;
}

std::vector<GameObject*>& Game::getObjects()
{
	return (this->objects);
}

void	Game::startGame()
{
	this->player = new Player(Position(this->bounding_box.getWidth() / 2, this->bounding_box.getHeight() - 3), this, 10);
	this->addObject(this->player);
	this->home->setActive(false);
}

void	Game::stopGame()
{
	for (auto object : this->objects)
		delete object;
	for (auto object : this->objects_to_add)
		delete object;
	this->objects.clear();
	this->objects_to_add.clear();
	this->score = 0;
	this->tick = 0;
	this->home->setActive(true);
}

void	Game::Update()
{
	if (this->home->isActive())
		return ;
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
			if (this->home->isActive())
				return ;
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
    mvprintw(LINES - 1, COLS - 9, "Time: %d", (std::chrono::steady_clock::now() - begin).count() / 1000000000);
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

Enemy*	Game::getRandomEnemy()
{
	int x = rand() % (this->getBounds().getWidth() - 4) + 2;
	int y = 1;
	int	factor = this->score > 1700 ? 1700 : (this->score + 1);
	int	rn = rand() % factor;

	if (rn < 700)
	{
		int dir = rand() % 2 == 0 ? 1 : -1;
		return (new DiagonalEnemy(Position(x, y), this, 1, dir));
	}
	else if (rn < 1000)
		return (new Enemy(Position(x, y), CollisionBox(1, 1), this, 1, 1));
	else if (rn < 1300)
		return (new DiagonalShootingEnemy(Position(x, y), this, 1));
	else if (rn < 1700)
		return (new HatcherEnemy(Position(x, y), this, 1));
	return (nullptr);
}

void	Game::spawnEnemies()
{
	tick++;
	if (rand() % (score + 20) > tick)
		return;
	tick-= 20;
	if (tick < 0)
		tick = 0;
	Enemy *enemy = this->getRandomEnemy();
	if (enemy)
		this->addObject(enemy);
}

void	Game::setExitMessage(std::string message)
{
	this->exit_message = message;
}

void	Game::printExit()
{
	std::cerr << this->exit_message << std::endl;
}
