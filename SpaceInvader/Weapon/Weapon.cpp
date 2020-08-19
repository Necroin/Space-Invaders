#include "Weapon.h"

Weapon::Weapon(ProjectileList& projectiles, int fire_delay, int damage) : 
	AutoResetTimer<>(fire_delay),
	_projectiles(projectiles),
	_damage(damage)
{}

int Weapon::damage() const
{
	return _damage;
}

IEvent<int>& Weapon::damage_change_event()
{
	return _damage_change_event;
}
