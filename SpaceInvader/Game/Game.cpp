#include "Game.h"

Game::Game() : _map(0, 0, 150, 40)
{
	_map.show_frame();
	_map.show();
	_player = std::make_unique<Player>(_map, _player_projectiles);
}

Game::~Game()
{
}

void Game::action()
{
	_player->action();
}

void Game::update()
{
	_map.update();
	_player->update();
}

void Game::render()
{
}

bool Game::is_active()
{
	return _active;
}
