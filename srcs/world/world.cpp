#include "world.hpp"
#include "game.hpp"

World::World(Game *game, Position pos, CollisionBox bounds): game(game), position(pos), bounds(bounds)
{
	this->ticks = 0;
}

World::~World()
{
	for (auto object : this->stars)
		delete object;
}

bool	World::init()
{
	if (!this->parse_rocks("./assets/rocks"))
	{
		return (false);
	}
	for (int y = 0; y < LINES; y++)
	{
		for (int i = 0; i < COLS; i++)
		{
			if (1 + std::rand() / ((RAND_MAX + 1u) / 100) == 1)
				this->stars.push_back(new Position(i, y));
			mvprintw(y, i, ".");
		}
	}
	this->rocks.push_back(new Rock(Position(10, 10), &this->sprites[0]));
	this->rocks[0]->draw();
	return (true);
}

bool	World::parse_rocks(std::string path)
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
		std::cerr << buff << std::endl;
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
	for (int i = 0; i < COLS - this->game->getOffset().getY() * 2; i++)
	{
		// std::cerr << 1 + std::rand() / ((RAND_MAX + 1u) / 50) << std::endl;
		if (1 + std::rand() / ((RAND_MAX + 1u) / 1000) == 1)
			this->stars.push_back(new Position(i, 0));
	}
	auto it = this->stars.begin();
	while (it != this->stars.end())
	{
		if ((*it)->getY() >= this->bounds.getHeight())
		{
			delete *it;
			it = this->stars.erase(it);
		}
		it++;
	}
	for (auto s : this->stars)
	{
		if (ticks % 10 == 1)
			s->setY(s->getY() + 1);
		mvprintw(s->getY(), s->getX(), ".");
	}
	if (1 + std::rand() / ((RAND_MAX + 1u) / this->rock_factor) == 1)
	{
		std::cerr << "rock " << this->ticks << std::endl;
	}
	this->ticks++;
}
