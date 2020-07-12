#pragma once
#ifndef _RAILGUN_H_
#define _RAILGUN_H_
#include "../Weapon.h"
#include "../../ECS/Components/Base/Timer/Timer.h"

class Railgun : public Weapon
{
private:
	class RailgunProjectile : public Projectile
	{
	public:
		RailgunProjectile(Map& map, DamageComponent::damage_function_type damage, int delay_time, int x, int y, int forward_direction, int symbol, int color = VisibleComponent::Color::White);
		virtual bool action() override;
	};
private:
	Entity& _parent;
	int _projectile_action_delay_time = 20;
	int _color;
	int _forward_direction;
public:
	Railgun(Entity& parent, Map& _map, ProjectileList& projectiles, int input_delay, int forward_direction, int color = VisibleComponent::Color::White);
	virtual void shoot() override;
};
#endif