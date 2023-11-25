#include <ncurses.h>
#include "bullet.hpp"
#include "player.hpp"
#include "game.hpp"
#include <thread>

int	main(void)
{
	Game game;
	game.getObjects().push_back(new Bullet(Position(0, 0), 1));
	game.getObjects().push_back(new Player(Position(0, 0), 100));
	initscr();
	while (1)
	{
		clear();
		game.Tick();
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	endwin();
	return (0);
}