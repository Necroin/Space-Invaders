#include "Game.h"

Game::Game() : _map(0, 0, 100, 40)
{
	_map.show_frame();
	_map.show();
	_player = std::make_unique<Player>(_map, _player_projectiles);
	_enemies.emplace_back(std::make_unique<Interceptor>(_map, _enemies_projectiles, 90, 20));
}

Game::~Game()
{
}

void Game::action()
{
	_player->action();
	for (auto&& enemy : _enemies) {
		enemy->action();
	}
}

void Game::update()
{
	_map.update();
	_player->update();
	for (auto&& enemy : _enemies) {
		enemy->update();
	}
}

void Game::render()
{
}

bool Game::is_active()
{
	return _active;
}
