#include "rock.hpp"

Rock::Rock(Position pos, std::string *buff): position(pos), buff(buff)
{
}

Rock::~Rock()
{

}

void	Rock::draw()
{
	int	x = this->position.getX();
	int	y = this->position.getY();

	for (auto i : *this->buff)
	{
		
	}
}