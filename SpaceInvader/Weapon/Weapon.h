#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "../Projectile/Projectile.h"

class Weapon {
protected:
	ProjectileList& _projectiles;
public:
	Weapon(ProjectileList& projectiles) : _projectiles(projectiles) {}
	virtual void action() {};
	virtual void update() {};
};
#endif