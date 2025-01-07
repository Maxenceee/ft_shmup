#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <functional>
#include "position.hpp"
#include "colors.hpp"

class Game;

class HButton
{
private:
	Position				pos;
	std::string				text;
	bool					selected = false;
	std::function<void ()>	func;

public:
	HButton(std::string text, std::function<void ()> func);
	~HButton();

	void		draw();
	void		setSelected(bool);
	void		place(Position pos);
	int			getSize();
	void		action();
};

class Home
{
private:
	bool	is_active = true;
	uint32_t	current = 0;
	Game	*game;

	std::vector<HButton *>	buttons;
	
	void	printName(int *y);
	void	placeButtons(int *y);

public:
	Home(Game *game);
	~Home();

	void	update();
	bool	isActive();
	void	setActive(bool active);
};
