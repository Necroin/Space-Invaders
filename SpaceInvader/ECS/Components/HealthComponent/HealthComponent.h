#pragma once
#ifndef _HEALTHCOMPONENT_H_
#define _HEALTHCOMPONENT_H_
#include "../../ECS.h"
#include "../DamageComponent/DamageComponent.h"
#include "../../../EventSystem/EventSystem.h"

class HealthComponent : 
	public Component
{
private:
	int _health;
	int _shield;
	Event<int> _changed_event;
public:
	HealthComponent(int health, int shield = 0);
	bool apply_damage(const DamageComponent& damage_component);
	virtual Component* copy() const override;
	int value();
public:
	IEvent<int>& changed_event();
};
#endif