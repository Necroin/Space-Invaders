#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "../Projectile/Projectile.h"

class Weapon : public AutoResetTimer<> {
protected:
	ProjectileList& _projectiles;
public:
	Weapon(ProjectileList& projectiles, int fire_delay);
	virtual void shoot() = 0;
};
#endif