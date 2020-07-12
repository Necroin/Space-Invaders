#include "Weapon.h"

Weapon::Weapon(Map& map, ProjectileList& projectiles, int fire_delay) : 
	AutoResetTimer<>(fire_delay),
	_projectiles(projectiles), 
	_map(map)
{}

void Weapon::action()
{
	decltype(auto) projectile_iterator = _projectiles.begin();
	while (projectile_iterator != _projectiles.end()) {
		decltype(auto) projectile = *projectile_iterator;
		if (!projectile->action()) {
			decltype(auto) delete_projectile_iterator = projectile_iterator;
			++projectile_iterator;
			_projectiles.data().erase(delete_projectile_iterator);
		}
		else {
			++projectile_iterator;
		}
	}
}

void Weapon::update()
{
	decltype(auto) projectile_iterator = _projectiles.begin();
	while (projectile_iterator != _projectiles.end()) {
		decltype(auto) projectile = *projectile_iterator;
		if (!projectile->update()) {
			decltype(auto) delete_projectile_iterator = projectile_iterator;
			++projectile_iterator;
			_projectiles.data().erase(delete_projectile_iterator);
		}
		else {
			++projectile_iterator;
		}
	}
}
