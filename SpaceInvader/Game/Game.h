#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "../Map/Map.h"
#include "../Entity/Player/Player.h"

class Game {
private:
	Map _map;
	std::unique_ptr<Player> _player;
	std::list<std::unique_ptr<Entity>> _enemies;
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