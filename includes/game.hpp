#pragma once

#include <iostream>
#include "game_object.hpp"
#include <vector>
#include "collision_box.hpp"

class Game
{
private:
	CollisionBox	bounding_box;
	uint32_t		offset_y;

	std::vector<GameObject*> objects;
	std::vector<GameObject*> objects_to_add;
	void Update();
	void Draw();
public:
	Game(CollisionBox bounding_box, uint32_t nb_player = 1);
	~Game();
	void Tick();

	std::vector<GameObject*>&	getObjects();

	void	addObject(GameObject *obj);
};
