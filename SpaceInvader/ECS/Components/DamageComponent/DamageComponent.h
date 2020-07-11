#pragma once
#ifndef _DAMAGECOMPONENT_H_
#define _DAMAGECOMPONENT_H_
#include <functional>
#include "../../ECS.h"

class DamageComponent : public Component {
public :
	using damage_function_type = std::function<bool(int&, int&)>;
private:
	damage_function_type _damage_function;
public:
	DamageComponent(damage_function_type damage_function);
	bool operator()(int& health_points, int& shield) const;
	virtual Component* copy() override;
};

auto default_damage(int damage) {
	return [_damage = damage](int& health_points, int& shield) -> bool
	{
		if (shield > 0) {
			shield -= _damage;
			if (shield <= 0) shield = 0;
		}
		else {
			health_points -= _damage;
			if (health_points <= 0) health_points = 0;
			return false;
		}
		return true;
	};
}
#endif