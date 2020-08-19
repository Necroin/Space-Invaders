#pragma once
#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "../Body/MechBody.h"

class Enemy : 
	public MechBody 
{
private:
	int _money_reward = 10;
	int _scrore_reward = 10;
public:
	virtual ~Enemy();
public:
	virtual void action() = 0;
	virtual void update() = 0;
	virtual void on_collide(const ColliderComponent& collider_component);
	int money_reward() const;
	int scrore_reward() const;
};
#endif