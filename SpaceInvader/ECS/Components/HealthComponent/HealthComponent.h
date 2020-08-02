#pragma once
#ifndef _HEALTHCOMPONENT_H_
#define _HEALTHCOMPONENT_H_
#include "../../ECS.h"
#include "../DamageComponent/DamageComponent.h"

class HealthComponent : 
	public Component
{
private:
	int _health;
	int _shield;
	bool _changed;
public:
	HealthComponent(int health, int shield = 0);
	bool apply_damage(const DamageComponent& damage_component);
	virtual Component* copy() const override;
	bool is_changed();
	int value();
	virtual void update() override;
};
#endif