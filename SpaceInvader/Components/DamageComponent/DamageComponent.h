#pragma once
#ifndef _DAMAGECOMPONENT_H_
#define _DAMAGECOMPONENT_H_
#include <functional>

class DamageComponent {
public :
	using damage_type = std::function<bool(int&, int&)>;
protected:
	damage_type _damage;
public:
	DamageComponent(damage_type damage) : _damage(damage) {}
	const damage_type& damage() const noexcept { return _damage; }
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