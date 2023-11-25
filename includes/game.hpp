#ifndef GAME_HPP
# define GAME_HPP
# include "gameobject.hpp"
# include <vector>

class Game
{
private:
	std::vector<GameObject*> objects;
	void Update();
	void Draw();
public:
	Game();
	~Game();
	void Tick();

	std::vector<GameObject*>& getObjects();
};
#endif