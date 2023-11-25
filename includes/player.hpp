#pragma once

#include <game_object.hpp>

class Player : public GameObject
{
private:
	int health;

public:
	Player();
	Player(Position position, Game *game, int health);
	~Player();

	void	update() override;
	void	draw() override;
	bool	shouldDelete() override;

	int		getHealth() const;
	void	shoot(Game *game);
};