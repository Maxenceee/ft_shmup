#pragma once

#include <ncurses.h>
#include <iostream>
#include "game_object.hpp"
#include <vector>
#include "collision_box.hpp"
#include "world.hpp"

#define SCORE_MULTIPLIER 1
#define MAIN_WIN_COLOR 2

class Game
{
private:
	CollisionBox	bounding_box;
	Position		offset;
	int				score = 0;
	World			*world;

	std::vector<GameObject*> objects;
	std::vector<GameObject*> objects_to_add;
	void Update();
	void Draw();
public:
	Game(CollisionBox bounding_box, uint32_t nb_player = 1);
	~Game();
	void	Tick();
	bool	exit = false;

	std::vector<GameObject*>&	getObjects();

	void	addObject(GameObject *obj);
	void	addScore(int score);
};
