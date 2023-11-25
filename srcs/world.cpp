#include "world.hpp"

World::World(Position pos, CollisionBox bounds): position(pos), bounds(bounds)
{
	this->ticks = 0;

	for (int y = 0; y < LINES; y++)
	{
		for (int i = 0; i < COLS; i++)
		{
			if (1 + std::rand() / ((RAND_MAX + 1u) / 100) == 1)
				this->stars.push_back(new Position(i, y));
			mvprintw(y, i, ".");
		}
	}
	if (!parse_rocks("./assets/rocks"))
	{
		std::cerr << "Could not find assets directory" << std::endl;
		/**
		 * TODO:
		 * Remove exit and end game well
		 */
		exit(1);
	}
}

World::~World()
{
	for (auto object : this->stars)
		delete object;
}

bool	World::parse_rocks(std::string path)
{
	if (!fs::exists(path))
		return (false);
	for (const auto & entry : fs::directory_iterator(path))
		std::cerr << entry.path() << std::endl;
	return (true);
}

void	World::update()
{
	for (int i = 0; i < COLS; i++)
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
