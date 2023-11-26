#include "player.hpp"
#include "game.hpp"
#include <ncurses.h>
#include "colors.hpp"
#include "bullet.hpp"

Player::Player() : Shooter()
{
	this->team = ObjectTeam::PLAYER;
}
Player::Player(Position position, Game *game, int health) : Shooter(position, CollisionBox(5, 3), game, health, 4, ObjectTeam::PLAYER)
{
	this->reset_invincibility = 24;
}
Player::~Player()
{
}

void Player::update()
{
	Shooter::update();
	int input = get_key();

	while (input != ERR) {
		if (input == 27)
		{
			this->getGame()->stopGame();
			return ;
		}
		if (input == KEY_UP)
			this->getPosition().setY(this->getPosition().getY() - 1);
		else if (input == KEY_DOWN)
			this->getPosition().setY(this->getPosition().getY() + 1);
		else if (input == KEY_LEFT)
			this->getPosition().setX(this->getPosition().getX() - 1);
		else if (input == KEY_RIGHT)
			this->getPosition().setX(this->getPosition().getX() + 1);
		else if (input == ' ' && this->shootcooldown == 0)
		{
			Position bullet_pos = this->getPosition();
			bullet_pos.setY(bullet_pos.getY() - 1);
			this->shoot(this->getGame(), bullet_pos, 1, Position(0, -1));
		}

		if (this->getPosition().getX() < 1)
			this->getPosition().setX(1);
		else if (this->getPosition().getX() >= this->getGame()->getBounds().getWidth() - 2)
			this->getPosition().setX(this->getGame()->getBounds().getWidth() - 3);
		else if (this->getPosition().getY() < 1)
			this->getPosition().setY(1);
		else if (this->getPosition().getY() >= this->getGame()->getBounds().getHeight() - 1)
			this->getPosition().setY(this->getGame()->getBounds().getHeight() - 2);

		input = get_key();
	}
}

bool Player::shouldDelete()
{
	return (false);
}

void	Player::damage(int damage)
{
	Shooter::damage(damage);
	if (this->health <= 0)
		this->getGame()->stopGame();
}

void Player::draw()
{
	if (invincibility > 0 && invincibility % 2 == 0)
		return ;
	int x = this->getPosition().getX() + this->getGame()->getOffset().getX();
	int y = this->getPosition().getY() + this->getGame()->getOffset().getY();

	attron(COLOR_PAIR(PLAYER_PAIR));
	mvprintw(y, x, "🛸");
	attroff(COLOR_PAIR(PLAYER_PAIR));
}
