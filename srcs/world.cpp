#include "world.hpp"

World::World(Position pos, CollisionBox bounds): position(pos), bounds(bounds)
{
	this->map = std::vector<std::vector<int>>(bounds.getHeight());
	std::fill(this->map.begin(), this->map.end(), std::vector<int>(bounds.getWidth(), 1));
}

World::~World()
{
}

void	World::draw()
{
	int	y = this->position.getY();

	for (auto vec : this->map)
	{
		int	x = this->position.getX();
		for (auto i : vec)
		{
			mvprintw(y, x, "1");
			x++;
		}
		y++;
	}
}
