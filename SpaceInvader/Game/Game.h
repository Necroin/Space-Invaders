#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Enemy/EnemySpawner/EnemySpawner.h"
#include "../UI/UI.h"

class Game {
private:
	std::unique_ptr<Player> _player;
	std::list<std::unique_ptr<Enemy>> _enemies;
	ProjectileList _player_projectiles;
	ProjectileList _enemies_projectiles;
	std::unique_ptr<EnemySpawner> _enemy_spawner;
	std::unique_ptr<PushButton> _exit_button;
	std::unique_ptr<HorizontalLayout> _player_stats;
public:
	Game();
	~Game();
public:
	void action();
	void update();
	void render();
private:
	bool _active = true;
public:
	bool is_active();
};
#endif