#include "Weapon.h"

Weapon::Weapon(ProjectileList& projectiles, int fire_delay) : 
	AutoResetTimer<>(fire_delay),
	_projectiles(projectiles)
{}