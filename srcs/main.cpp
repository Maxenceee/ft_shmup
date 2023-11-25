#include <ncurses.h>
#include "player.hpp"
#include "game.hpp"
#include <thread>
#include "unistd.h"
#include "colors.hpp"
#include <locale.h>
#include <stdio.h>

void	init_color_pairs()
{
	// player 
	init_pair(PLAYER_PAIR, COLOR_GREEN, COLOR_BLACK);
}

int	main(void)
{
	Game game(CollisionBox(COLS, LINES));

	if (!isatty(STDOUT_FILENO))
	{
		std::cerr << "Invalid stdand out" << std::endl;
		return (1);
	}
	setlocale(LC_ALL, "");
	game.getObjects().push_back(new Player(Position(10, 10), 100));
	WINDOW *win = initscr();
	start_color();
	init_color_pairs();
	nodelay(win, true);
	noecho();
	curs_set(0);
	while (1)
	{
		clear();
		game.Tick();
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	endwin();
	curs_set(1);
	return (0);
}