#include "home.hpp"
#include "game.hpp"

Home::Home(Game *game): game(game)
{
	this->buttons.push_back(new HButton("Play", [=]() {this->game->startGame();}));
	this->buttons.push_back(new HButton("Quit", [=]() {this->game->exit = true;}));
}

Home::~Home()
{
	for (auto b : this->buttons)
		delete b;
}

void	Home::update()
{
	int	start = LINES * 25 / 100;

	this->printName(&start);
	int input = get_key();

	if (input == 27)
	{
		this->game->exit = 1;
		return ;
	}
	else if (input == KEY_UP)
		this->current = (this->current - 1) % this->buttons.size();
	else if (input == KEY_DOWN)
		this->current = (this->current + 1) % this->buttons.size();
	else if (input == '\n')
		this->buttons[this->current]->action();
	
	for (uint32_t i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->setSelected(i == this->current);
	}
	this->placeButtons(&start);
}

void	Home::printName(int *y)
{
	int	x = (COLS - 46) / 2;
	attron(COLOR_PAIR(HOME_TITLE));
	mvprintw(*y, x, "______ _____ _____ _   _ ___  ____   _______");
	mvprintw(*y + 1, x, "|  ___|_   _/  ___| | | ||  \\/  | | | | ___ \\");
	mvprintw(*y + 2, x, "| |_    | | \\ `--.| |_| || .  . | | | | |_/ /");
	mvprintw(*y + 3, x, "|  _|   | |  `--. \\  _  || |\\/| | | | |  __/");
	mvprintw(*y + 4, x, "| |     | | /\\__/ / | | || |  | | |_| | |");
	mvprintw(*y + 5, x, "\\_|     \\_/ \\____/\\_| |_/\\_|  |_/\\___/\\_|");
	attroff(COLOR_PAIR(HOME_TITLE));
	(*y) += 5;
	if (this->game->lastScore > 0)
	{
		int	p = LINES * 5 / 100;
		(*y) += p;
		mvprintw(*y, x, "Last score: %d", this->game->lastScore);
		(*y) += LINES * 15 / 100 - p;
	}
	else
		(*y) += LINES * 15 / 100;
}

void	Home::placeButtons(int *y)
{
	int	x;

	for (auto b : this->buttons)
	{
		x = (COLS - b->getSize()) / 2;
		b->place(Position(x, *y));
		b->draw();
		(*y) += 3;
		(*y) += LINES * 5 / 100;
	}
}

bool	Home::isActive()
{
	return (this->is_active);
}

void	Home::setActive(bool active)
{
	this->is_active = active;
}

/**
 *
 * Home Button 
 * 
 */

HButton::HButton(std::string text, std::function<void ()> func): text(text), func(func)
{
}

HButton::~HButton()
{
}

void	HButton::action()
{
	this->func();
}

void	HButton::place(Position pos)
{
	this->pos = pos;
}

int		HButton::getSize()
{
	return (this->text.length() + 2 + 2);
}

void	HButton::setSelected(bool isselected)
{
	this->selected = isselected;
}

void	HButton::draw()
{
	int	l = this->text.length() + 2;
	int	y = this->pos.getY();

	if (this->selected)
	{
		int	x = this->pos.getX();
		for (int i = 0; i < l + 4; i++)
		{
			if (i == 0)
				mvprintw(y, x, "╔");
			else if (i == l + 3)
				mvprintw(y, x, "╗");
			else
				mvprintw(y, x, "═");
			x++;
		}
		y++;
		x = this->pos.getX();
		mvprintw(y, x, "║  %s  ║", this->text.c_str());
		y++;
		for (int i = 0; i < l + 4; i++)
		{
			if (i == 0)
				mvprintw(y, x, "╚");
			else if (i == l + 3)
				mvprintw(y, x, "╝");
			else
				mvprintw(y, x, "═");
			x++;
		}
	}
	else 
	{
		int	x = this->pos.getX();
		for (int i = 0; i < l + 4; i++)
		{
			if (i == 0)
				mvprintw(y, x, "┌");
			else if (i == l + 3)
				mvprintw(y, x, "┐");
			else
				mvprintw(y, x, "─");
			x++;
		}
		y++;
		x = this->pos.getX();
		mvprintw(y, x, "│  %s  │", this->text.c_str());
		y++;
		for (int i = 0; i < l + 4; i++)
		{
			if (i == 0)
				mvprintw(y, x, "└");
			else if (i == l + 3)
				mvprintw(y, x, "┘");
			else
				mvprintw(y, x, "─");
			x++;
		}
	}
}
