#include "player.hpp"
#include "game.hpp"
#include <ncurses.h>
#include "colors.hpp"
#include "bullet.hpp"

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

Player::Player() : GameObject(Position(0, 0), CollisionBox(5, 3))
{
    this->health = 100;
}
Player::Player(Position position, int health) : GameObject(position, CollisionBox(5, 3))
{
    this->health = health;
}
Player::~Player()
{
}

void Player::update(Game *game)
{
    int input = get_key();

    if (input == KEY_UP)
        this->getPosition().setY(this->getPosition().getY() - 1);
    else if (input == KEY_DOWN)
        this->getPosition().setY(this->getPosition().getY() + 1);
    else if (input == KEY_LEFT)
        this->getPosition().setX(this->getPosition().getX() - 1);
    else if (input == KEY_RIGHT)
        this->getPosition().setX(this->getPosition().getX() + 1);
    else if (input == ' ')
        this->shoot(game);

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
        if (this->collidesWith(game->getObjects()[i]) && this != game->getObjects()[i])
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
    int x = this->getPosition().getX();
    int y = this->getPosition().getY();

    attron(COLOR_PAIR(PLAYER_PAIR));
    mvprintw(y, x, "🛸");
    // mvprintw(y - 1, x, "_");
    // mvprintw(y, x - 1, "/ \\");
    // mvprintw(y + 1, x - 2, "<o0o>");
    attroff(COLOR_PAIR(PLAYER_PAIR));
}

void    Player::shoot(Game *game)
{
    int x = this->getPosition().getX();
    int y = this->getPosition().getY();

    game->addObject(new Bullet(Position(x, y - 1), 1));
}