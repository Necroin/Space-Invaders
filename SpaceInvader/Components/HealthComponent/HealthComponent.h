#pragma once
#ifndef _HEALTHCOMPONENT_H_
#define _HEALTHCOMPONENT_H_
#include "../GetDamageComponent/GetDamageComponent.h"

class HealthComponent : public GetDamageComponent {
protected:
	mutable int _health_points;
	mutable int _shield;
public:
	HealthComponent(int health_points, int shield = 0) : _health_points(health_points), _shield(shield) {}
	virtual bool damage_this(const Projectile& projectile) const override {
		return projectile.damage()(_health_points, _shield);
	}

};
#endif