#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(ProjectileList& enemies_projecitles, std::list<std::unique_ptr<Enemy>>& enemies) :
	_enemies_projectiles(enemies_projecitles),
	_enemies(enemies),
	_interceptors_count(0)
{}

void EnemySpawner::action()
{
	if (_interceptors_count < 5) {
		int x = std::uniform_int_distribution<int>(Map::width() - 10, Map::width())(_random_device);
		int y = std::uniform_int_distribution<int>(Map::y(), Map::height())(_random_device);
		_enemies.emplace_back(std::make_unique<Interceptor>(_enemies_projectiles, x, y));
		_enemies.back()->add_component<ReferenceCounterComponent>(_interceptors_count);
	}

}
