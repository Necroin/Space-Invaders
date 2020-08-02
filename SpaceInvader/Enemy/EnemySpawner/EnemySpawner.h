#pragma once
#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_
#include "../Interceptor/Interceptor.h"
#include <random>

class EnemySpawner {
private:
	std::list<std::unique_ptr<Enemy>>& _enemies;
	ProjectileList& _enemies_projectiles;
	std::random_device _random_device;
	std::size_t _interceptors_count;
public:
	EnemySpawner(ProjectileList& enemies_projecitles, std::list<std::unique_ptr<Enemy>>& enemies);
	void action();
};
#endif