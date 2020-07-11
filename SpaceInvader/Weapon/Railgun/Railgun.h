#pragma once
#ifndef _RAILGUN_H_
#define _RAILGUN_H_
#include "../Weapon.h"
#include "../../ECS/Components/Base/Timer/Timer.h"

class Railgun : public Weapon
{
private:
	Entity& _parent;
	AutoResetTimer<> _shoot_delay_timer;
	int _projectile_action_delay_time = 20;
public:
	Railgun(Entity& parent, ProjectileList& projectiles);
	virtual void action() override;
	virtual void update() override;
};
#endif