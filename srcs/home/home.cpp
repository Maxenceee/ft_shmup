#include "home.hpp"
#include "game.hpp"

Home::Home(Game *game): game(game)
{
	this->buttons.push_back(new HButton("Play", [=]() {this->is_active = false;}));
	this->buttons.push_back(new HButton("Quit", [=]() {this->game->exit = true;}));
}

Home::~Home()
{
}

void	Home::update()
{
	int	start = 20;

	this->printName(&start);
	int input = get_key();

	if (input == KEY_UP)
		this->current = (this->current - 1) % this->buttons.size();
	else if (input == KEY_DOWN)
		this->current = (this->current + 1) % this->buttons.size();
	else if (input == KEY_ENTER)
		this->buttons[this->current].action();
	
	for (int i = 0; i < this->buttons.size(); i++)
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
	(*y) += 15;
}

void	Home::placeButtons(int *y)
{
	int	x;

	for (auto b : this->buttons)
	{
		x = (COLS - b->getSize()) / 2;
		b->place(Position(x, *y));
		b->draw();
		(*y) += 5;
	}
}

bool	Home::isActive()
{
	return (this->is_active);
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
	this.func();
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

	// std::cerr << "len " << l << " tex " << this->text << std::endl;

	// std::string	charset;
	if (this->selected)
	{
		// charset = "╔╗║╚╝═";
		int	x = this->pos.getX();
		for (int i = 0; i < l + 4; i++)
		{
			std::cerr << "i " << i << std::endl;
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
		// charset = "┌┐│└┘─";
		int	x = this->pos.getX();
		for (int i = 0; i < l + 4; i++)
		{
			std::cerr << "i " << i << std::endl;
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
	// mvprintw(10, 10, "╔════════╗");
	// mvprintw(11, 10, "║  Play  ║");
	// mvprintw(12, 10, "╚════════╝");
	// mvprintw(15, 10, "┌────────┐");
	// mvprintw(16, 10, "│  Play  │");
	// mvprintw(17, 10, "└────────┘");
}