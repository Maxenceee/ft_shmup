#include "shooter.hpp"
#include "bullet.hpp"
#include "game.hpp"

Shooter::Shooter()
{
    this->position = Position(0, 0);
    this->game = nullptr;
    this->health = 0;
    this->reset_shootcooldown = 0;
    this->team = ObjectTeam::ENEMY;
}

Shooter::Shooter(Position position, CollisionBox bounding_box, Game *game, int health, int reset_shootcooldown, ObjectTeam team)
{
    this->position = position;
    this->game = game;
    this->health = health;
    this->reset_shootcooldown = reset_shootcooldown;
    this->team = team;
}

Shooter::~Shooter()
{
}

void    Shooter::update()
{
    if (this->shootcooldown > 0)
        this->shootcooldown--;
    if (this->invincibility > 0)
    {
        this->invincibility--;
        return;
    }
    for (int i = 0; i < this->getGame()->getObjects().size(); i++)
    {
        if (this->getTeam() != this->getGame()->getObjects()[i]->getTeam() 
            && this->collidesWith(this->getGame()->getObjects()[i]) \
            && this->getGame()->getObjects()[i]->isShooter())
        {
            this->damage(1);
            this->getGame()->getObjects()[i]->getPosition().setY(-1);
            break;
        }
    }
}

bool    Shooter::shouldDelete()
{
    if (this->health <= 0)
        return (true);
    return (false);
}

bool    Shooter::isShooter()
{
    return (true);
}

void    Shooter::damage(int damage)
{
    if (this->invincibility > 0)
        return;
    this->health -= damage;
    this->invincibility = this->reset_invincibility;
}

int		Shooter::getHealth() const
{
    return (this->health);
}

int     Shooter::getKillReward() const
{
    return (this->killreward);
}

void	Shooter::shoot(Game *game, Position bullet_pos, int damage, int dir)
{
    if (this->shootcooldown == 0)
    {
        game->addObject(new Bullet(bullet_pos, game, damage, this->team, dir));
        this->shootcooldown = this->reset_shootcooldown;
    }
}