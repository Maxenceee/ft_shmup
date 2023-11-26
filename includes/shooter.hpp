#pragma once
#include "game_object.hpp"

class Shooter : public GameObject
{
protected:
    int	shootcooldown = 0;
    int reset_shootcooldown = 10;
    int invincibility = 0;
    int reset_invincibility = 0;
    int killreward = 0;
    int health;
public:

    Shooter();
    Shooter(Position position, CollisionBox bounding_box, Game *game, int health, int reset_shootcooldown, ObjectTeam team);
    ~Shooter();

    virtual void	update() override;
    virtual bool    shouldDelete() override;

    bool    isShooter() override;

    void    damage(int damage);
    int		getHealth() const;
    int		getKillReward() const;
    void	shoot(Game *game, Position bullet_pos, int damage, Position dir);
};