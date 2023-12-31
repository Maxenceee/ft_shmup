#include "game.hpp"
#include "player.hpp"
#include "unistd.h"
#include "colors.hpp"
#include <locale.h>
#include "enemy.hpp"
#include "bullet.hpp"
#include "time.hpp"
#include "world.hpp"

int	ft_can_render(void)
{
	static time_t	str_time = 0;

	if (str_time == 0)
		str_time = ft_abs_time();
	if (ft_abs_time() - str_time >= 30)
	{
		str_time = ft_abs_time();
		return (1);
	}
	return (0);
}

void	init_color_pairs()
{
	init_pair(PLAYER_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(MAIN_WIN_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(HEARTS_PAIR, COLOR_RED, COLOR_BLACK);
	init_pair(ENEMY_BULLET_PAIR, COLOR_RED, COLOR_BLACK);
	init_pair(HOME_TITLE, COLOR_BLUE, COLOR_BLACK);
}

int	main(void)
{
	WINDOW *win_box;

	if (!isatty(STDOUT_FILENO))
	{
		std::cerr << "Invalid stdand out" << std::endl;
		return (1);
	}
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	init_color_pairs();
	nodelay(stdscr, true);
	noecho();
	curs_set(0);
	std::srand(time(nullptr));
	win_box = subwin(stdscr, LINES - 4, COLS - 10, 2, 5);

	Game game(CollisionBox(COLS - 10, LINES - 4), Position(5, 2), Position(COLS, LINES));
	while (!game.exit)
	{
		if (!ft_can_render())
			continue ;
		clear();
		box(win_box, ACS_VLINE, ACS_HLINE);
		if (game.checkDims(Position(COLS, LINES)))
		{
			delwin(win_box);
			win_box = subwin(stdscr, LINES - 4, COLS - 10, 2, 5);
		}
		game.Tick();
		refresh();
	}
	delwin(win_box);
	delwin(stdscr);
	endwin();
	curs_set(1);
	game.printExit();
	return (0);
}
