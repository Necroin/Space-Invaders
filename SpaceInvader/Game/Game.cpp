#include "Game.h"

Game::Game() : _map(0, 0, 150, 40)
{
	_player = std::make_unique<Player>(_map);
	_map.show();
}

Game::~Game()
{
}

void Game::action()
{
	_player->action(_enemies);
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
