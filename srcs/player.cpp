#include "player.hpp"
#include "game.hpp"
#include <ncurses.h>

Player::Player() : GameObject(Position(0, 0))
{
    this->health = 100;
}
Player::Player(Position position, int health) : GameObject(position)
{
    this->health = health;
}
Player::~Player()
{
}
bool Player::collidesWith(GameObject *other)
{
    if ((this->getPosition().getX() - 1 >= other->getPosition().getX() && this->getPosition().getX() + 1 <= other->getPosition().getX()) &&
        this->getPosition().getY() == other->getPosition().getY())
        return (true);
}

void Player::update(Game *game)
{
    int input = ();

    if (input == KEY_UP)
        this->getPosition().setY(this->getPosition().getY() - 1);
    else if (input == KEY_DOWN)
        this->getPosition().setY(this->getPosition().getY() + 1);
    else if (input == KEY_LEFT)
        this->getPosition().setX(this->getPosition().getX() - 1);
    else if (input == KEY_RIGHT)
        this->getPosition().setX(this->getPosition().getX() + 1);

    if (this->getPosition().getX() < 1)
        this->getPosition().setX(1);
    else if (this->getPosition().getX() > COLS - 2)
        this->getPosition().setX(COLS - 2);
    else if (this->getPosition().getY() < 1)
        this->getPosition().setY(1);
    else if (this->getPosition().getY() > LINES - 1)
        this->getPosition().setY(LINES - 1);
    
    for (int i = 0; i < game->getObjects().size(); i++)
    {
        if (this->collidesWith(game->getObjects()[i]))
        {
            this->health -= 10;
            game->getObjects()[i]->getPosition().setY(-1);
        }
    }
}

bool Player::shouldDelete()
{
    if (this->health <= 0)
        return (true);
    return (false);
}

void Player::draw()
{
    mvprintw(this->getPosition().getY(), this->getPosition().getX() - 1, "<o>");
}
