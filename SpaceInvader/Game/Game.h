#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Enemy/EnemySpawner/EnemySpawner.h"
#include "../UI/UI.h"
#include "../FSM/FSM.h"

class Game {
private:
	std::unique_ptr<Player> _player;
	std::list<std::unique_ptr<Enemy>> _enemies;
	ProjectileList _player_projectiles;
	ProjectileList _enemies_projectiles;
	std::unique_ptr<EnemySpawner> _enemy_spawner;


	std::unique_ptr<HorizontalLayout> _player_stats;
	std::unique_ptr<VerticalLayout> _menu_buttons;

	enum class GameState {
		Menu,
		Play
	};
	GameState _game_state;
	FSM::FSM<GameState> _game_fsm;
public:
	Game();
	~Game();
public:
	void action();
	void update();
	void render();

	void menu();

	void run();
private:
	bool _active = true;
public:
	bool is_active();
};
#endif