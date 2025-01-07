#include "world.hpp"
#include "game.hpp"

World::World(Game *game, Position pos): position(pos), game(game)
{
	this->ticks = 0;
}

World::~World()
{
	for (auto object : this->stars)
		delete object;
	for (auto object : this->Sprites)
		delete object;
}

bool	World::init()
{
	for (int y = 0; y < LINES; y++)
	{
		for (int i = this->game->getOffset().getX() + 1; i < COLS - this->game->getOffset().getX() * 2; i++)
		{
			if (1 + std::rand() / ((RAND_MAX + 1u) / 100) == 1)
				this->stars.push_back(new Position(i, y));
			mvprintw(y, i, ".");
		}
	}
	// this->Sprites.push_back(new Sprite(Position(10, 10), &this->sprites[0]));
	// this->Sprites.push_back(new Sprite(Position(50, 10), &this->sprites[1]));
	// this->Sprites.push_back(new Sprite(Position(100, 10), &this->sprites[2]));
	// this->Sprites.push_back(new Sprite(Position(150, 10), &this->sprites[3]));
	return (true);
}

bool	World::parse_Sprites(std::string path)
{
	int	i = 0;

	if (!fs::exists(path))
	{
		this->game->setExitMessage(B_RED"Could not find assets directory");
		return (false);
	}
	for (const auto & entry : fs::directory_iterator(path))
	{
		if (entry.path().extension() != ".sprite")
			continue ;
		std::string	buff = read_file(entry.path());
		this->sprites.push_back(buff);
		i++;
	}
	if (i == 0)
	{
		this->game->setExitMessage(B_RED"Assets directory is empty");
		return (false);
	}
	return (true);
}

void	World::update()
{
	this->renderStars();
	if (1 + std::rand() / ((RAND_MAX + 1u) / this->Sprite_factor) == 1)
	{
		std::cerr << "Sprite " << this->ticks << std::endl;
	}
	for (auto r : this->Sprites)
	{
		if (ticks % 15 == 1)
			r->getPosition()->setY(r->getPosition()->getY() + 1);
		r->draw();
	}
}

void	World::renderStars()
{
	for (int y = 0; y < this->game->getOffset().getY(); y++)
	{
		for (int x = 0; x < COLS; x++)
		{
			mvprintw(y, x, ".");
		}
	}
	for (int y = 0; y < LINES; y++)
	{
		for (int x = 0; x < this->game->getOffset().getX(); x++)
		{
			mvprintw(y, x, ".");
		}
	}
	for (int y = 0; y < this->game->getOffset().getY(); y++)
	{
		for (int x = 0; x < COLS; x++)
		{
			mvprintw(this->game->getBounds().getHeight() + this->game->getOffset().getY() + y, x, ".");
		}
	}
	for (int y = 0; y < LINES; y++)
	{
		for (int x = 0; x < this->game->getOffset().getX(); x++)
		{
			mvprintw(y, this->game->getBounds().getWidth() + this->game->getOffset().getX() + x, ".");
		}
	}
	for (int i = this->game->getOffset().getX() + 1; i < COLS - this->game->getOffset().getX() * 2; i++)
	{
		if (1 + std::rand() / ((RAND_MAX + 1u) / 1000) == 1)
			this->stars.push_back(new Position(i, this->game->getOffset().getY() + 1));
	}
	auto it = this->stars.begin();
	while (it != this->stars.end())
	{
		if ((*it)->getY() >= this->game->getBounds().getHeight())
		{
			delete *it;
			it = this->stars.erase(it);	
		}
		else
			it++;
	}
	for (auto s : this->stars)
	{
		if (ticks % 10 == 1)
			s->setY(s->getY() + 1);
		mvprintw(s->getY(), s->getX(), ".");
	}
	this->ticks++;
}
