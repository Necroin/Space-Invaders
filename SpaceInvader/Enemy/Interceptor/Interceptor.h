#pragma once
#ifndef _INTERCEPTOR_H_
#define _INTERCEPTOR_H_
#include "../Enemy.h"
#include "../../Map/Map.h"
#include "../../Projectile/Projectile.h"
#include "../../Weapon/Railgun/Railgun.h"

class Interceptor : public Enemy {
private:
	class AttackBodyElement : public BodyElement
	{
	private:
		Railgun _weapon;
	public:
		AttackBodyElement(Map& map, ProjectileList& projectiles);
		virtual void action() override;
		virtual void update() override;
	};
private:
	Map& _map;
	ProjectileList& _projectiles;
public:
	Interceptor(Map& map, ProjectileList& projectiles, int x, int y);
	virtual void action() override;
	virtual void update() override;
};
#endif