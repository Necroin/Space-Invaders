#pragma once
#ifndef _RAILGUN_H_
#define _RAILGUN_H_
#include "../Weapon.h"

class Railgun : public Weapon
{
private:
	class RailgunProjectile : public Projectile
	{
	public:
		RailgunProjectile(
			DamageComponent::damage_function_type damage, 
			int delay_time, 
			int x, 
			int y, 
			const PositionComponent::Direction& direction,
			int symbol, 
			int color = VisibleComponent::Color::White
		);
		virtual bool action() override;
	};
private:
	Entity& _parent;
	int _projectile_action_delay_time = 20;
	int _color;
public:
	Railgun(
		Entity& parent, 
		ProjectileList& projectiles, 
		int fire_delay,
		int color = VisibleComponent::Color::White);
	virtual void shoot() override;
};
#endif