#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "../Projectile/Projectile.h"
#include <string>

class Weapon : public AutoResetTimer<> {
protected:
	ProjectileList& _projectiles;
	int _damage;
	Event<int> _damage_change_event;
public:
	Weapon(ProjectileList& projectiles, int fire_delay, int damage);
	virtual void shoot() = 0;
	int damage() const;
	IEvent<int>& damage_change_event();
	virtual std::string& name() const = 0;
};
#endif