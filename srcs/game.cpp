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

Game::Game(CollisionBox bounding_box, Position pos, Position dims)
{
	this->bounding_box = bounding_box;
	this->offset = pos;
	this->dims = dims;
	this->world = new World(this, this->offset);
	if (!this->world->init())
		this->exit = true;
	if (!this->read_boss_sprite())
		this->exit = true;
	this->home = new Home(this);
}

Game::~Game()
{
	this->stopGame();
	delete this->world;
	delete this->home;
	if (this->current_boss)
		delete this->current_boss;
}

std::vector<GameObject*>& Game::getObjects()
{
	return (this->objects);
}

void	Game::startGame()
{
	begin = std::chrono::steady_clock::now();
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
	this->player = nullptr;
	this->objects.clear();
	this->objects_to_add.clear();
	this->lastScore = this->score;
	this->score = 0;
	this->tick = 0;
	this->home->setActive(true);
}

void	Game::Update()
{
	if (this->home->isActive())
		return ;
	if (!this->has_boss)
		spawnEnemies();
	this->score += SCORE_MULTIPLIER;

	auto it = this->objects.begin();
	while (it != this->objects.end())
	{
		if ((*it)->shouldDelete())
		{
			delete *it;
			it = this->objects.erase(it);
			if (this->home->isActive())
				return ;
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
	this->spawnBoss();
}

void    Game::addObject(GameObject *obj)
{
	this->objects_to_add.push_back(obj);
}

void	Game::Draw()
{
	if (!this->player)
		return ;
	int	max = this->player->getHealth();
	mvprintw(LINES - 4, (COLS - (1 + (max == 10))) / 2, "[%d]", max);
	attron(COLOR_PAIR(HEARTS_PAIR));
	mvprintw(LINES - 3, (COLS - max) / 2, " ");
	for (int i = 1; i < max + 1; i++)
	{
		mvprintw(LINES - 3, (COLS - max) / 2 + i, "❤️");
	}
	mvprintw(LINES - 3, (COLS - max) / 2 + max + 1, " ");
	attroff(COLOR_PAIR(HEARTS_PAIR));
	mvprintw(LINES - 3, 7, " Score: %d ", this->score);
	int time = (std::chrono::steady_clock::now() - begin).count() / 1000000000;
	int	l = [=]()
	{
		int	t = time;
		int	m = 0;
		while (t >= 10)
		{
			t /= 10;
			m++;
		}
		return (m);
	}();
	mvprintw(LINES - 3, COLS - (16 + l), " Time: %d ", time);

	for (auto object : this->objects)
		object->draw();
}

void	Game::Tick()
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
	tick++;
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

Home*	Game::getHome() const
{
	return (this->home);
}

Enemy*	Game::getRandomEnemy()
{
	int x = rand() % (this->getBounds().getWidth() - 4) + 2;
	int y = 1;
	int	factor = this->score > 1100 ? 1100 : (this->score + 1);
	int	rn = rand() % factor;

	if (rn < 700)
	{
		int dir = rand() % 2 == 0 ? 1 : -1;
		return (new DiagonalEnemy(Position(x, y), this, 1, dir));
	}
	else if (rn < 1000)
		return (new Enemy(Position(x, y), CollisionBox(1, 1), this, 1, 200));
	else if (rn < 1050)
		return (new DiagonalShootingEnemy(Position(x, y), this, 1));
	else if (rn < 1100)
		return (new HatcherEnemy(Position(x, y), this, 1));
	return (nullptr);
}

void	Game::spawnEnemies()
{
	if (rand() % (score + 20) > tick)
		return ;
	tick-= 20;
	if (tick < 0)
		tick = 0;
	Enemy *enemy = this->getRandomEnemy();
	if (enemy)
		this->addObject(enemy);
}

void	Game::spawnBoss()
{
	if (!this->has_boss && this->score % 3000 == 1 && this->score > 100)
	{
		this->current_boss = new Boss(this, this->boss_buff, 1, this->score / 100);
		this->addObject(this->current_boss);
	}
}

bool	Game::checkDims(Position ndims)
{
	if (this->dims.getX() != ndims.getX() || this->dims.getY() != ndims.getY())
	{
		this->bounding_box = CollisionBox(ndims.getX() - 10, ndims.getY() - 4);
		this->dims = ndims;
		this->stopGame();
		return (true);
	}
	return (false);
}

void	Game::setExitMessage(std::string message)
{
	this->exit_message = message;
}

void	Game::printExit()
{
	std::cerr << this->exit_message << std::endl;
}

void	Game::hasBoss(bool has)
{
	this->has_boss = has;
}

int		Game::read_boss_sprite()
{
	fs::path	path = "./assets/boss/1.boss";
	fs::path	sprite_bullet = "./assets/boss/boss_bullet.sprite";

	if (!fs::exists(path) || !fs::exists(sprite_bullet))
	{
		this->setExitMessage(B_RED"Assets directory is missing or empty");
		return (false);
	}
	this->bullet_sprite = read_file(sprite_bullet);
	this->boss_buff = read_file(path);
	return (true);
}
