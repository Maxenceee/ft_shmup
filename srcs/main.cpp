#include "game.hpp"
#include "player.hpp"
#include "unistd.h"
#include "colors.hpp"
#include <locale.h>
#include "enemy.hpp"
#include "bullet.hpp"
#include "time.hpp"
#include "mountains.hpp"

int	ft_can_render(void)
{
	static time_t	str_time = 0;

	if (str_time == 0)
		str_time = ft_abs_time();
	if (ft_abs_time() - str_time >= 16)
	{
		str_time = ft_abs_time();
		return (1);
	}
	return (0);
}

void	init_color_pairs()
{
	// player 
	init_pair(PLAYER_PAIR, COLOR_GREEN, COLOR_BLACK);
}

int	main(void)
{
	Game game(CollisionBox(COLS, LINES - 1));

	if (!isatty(STDOUT_FILENO))
	{
		std::cerr << "Invalid stdand out" << std::endl;
		return (1);
	}
	setlocale(LC_ALL, "");
	game.addObject(new Player(Position(10, 10), &game, 100));
	game.addObject(new Enemy(Position(30, 0), CollisionBox(1, 1), &game, 1, 200));
	WINDOW *win = initscr();
	start_color();
	init_color_pairs();
	nodelay(win, true);
	noecho();
	curs_set(0);
	// Mountains	m(Position(5, 5), CollisionBox(5, 5));
	while (!game.exit)
	{
		if (!ft_can_render())
			continue ;
		clear();
		game.Tick();
		// m.draw();
		refresh();
	}
	endwin();
	curs_set(1);
	return (0);
}