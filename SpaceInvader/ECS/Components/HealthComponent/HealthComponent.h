#pragma once
#ifndef _HEALTHCOMPONENT_H_
#define _HEALTHCOMPONENT_H_
#include "../../ECS.h"
#include "../DamageComponent/DamageComponent.h"

/**
constructor : HealthComponent(int health, int shield = 0)
methoods :
bool apply_damage(const DamageComponent& damage_component);
*/
class HealthComponent : public Component {
private:
	int _health;
	int _shield;
public:
	HealthComponent(int health, int shield = 0) :
		_health(health),
		_shield(shield)
	{}
	bool apply_damage(const DamageComponent& damage_component) {
		damage_component(_health, _shield);
	}
	virtual Component* copy() override {
		return new HealthComponent(_health, _shield);
	}
};
#endif