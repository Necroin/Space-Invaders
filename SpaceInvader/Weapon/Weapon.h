#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "../Projectile/Projectile.h"

class Weapon : public AutoResetTimer<> {
protected:
	ProjectileList& _projectiles;
	Map& _map;
public:
	Weapon(Map& map, ProjectileList& projectiles, int fire_delay);
	virtual void action();
	virtual void update();
	virtual void shoot() = 0;
};
#endif