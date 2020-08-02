#pragma once
#ifndef _INTERCEPTOR_H_
#define _INTERCEPTOR_H_
#include "../Enemy.h"
#include "../../Map/Map.h"
#include "../../Projectile/Projectile.h"
#include "../../Weapon/Railgun/Railgun.h"

class Interceptor : 
	public Enemy 
{
private:
	class AttackBodyElement : 
		public BodyElement
	{
	private:
		Railgun _weapon;
	public:
		AttackBodyElement(ProjectileList& projectiles);
		virtual void action() override;
		virtual void update() override;
	};
private:
	ProjectileList& _projectiles;
	AutoResetTimer<> _input_delay_timer;
	inline static const size_t _input_dalay_time = 100;
public:
	Interceptor(ProjectileList& projectiles, int x, int y);
	virtual ~Interceptor() override;
	virtual void action() override;
	virtual void update() override;
};
#endif