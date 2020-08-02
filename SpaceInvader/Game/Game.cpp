#include "Game.h"
#include "../WinAPI/WinAPI.h"

Game::Game()
{
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);

	decltype(auto) hInput = GetStdHandle(STD_INPUT_HANDLE);
	decltype(auto) hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD console_prev_mode;
	GetConsoleMode(hInput, &console_prev_mode);
	SetConsoleMode(hInput, console_prev_mode & ~ENABLE_QUICK_EDIT_MODE);

	Map::create(0, 0, 100, 40);
	Map::show_frame();
	Map::show();
	_player = std::make_unique<Player>(_player_projectiles);
	_enemy_spawner = std::make_unique<EnemySpawner>(_enemies_projectiles, _enemies);
	_player_stats = std::make_unique<HorizontalLayout>(Map::frame_x() + Map::frame_width() + 1, Map::frame_y() + 1);
	decltype(auto) player_stats_names = _player_stats->add_object<VerticalLayout>(_player_stats.get());
	player_stats_names.add_object<Text>("Money : ");
	player_stats_names.add_object<Text>("Health : ");
	player_stats_names.add_object<Text>("Attack : ");
	player_stats_names.set_model(VerticalLayout::Model::left);
	decltype(auto) player_stats_values = _player_stats->add_object<VerticalLayout>(_player_stats.get());
	player_stats_values.add_object<Text>("");
	player_stats_values.add_object<Text>(std::to_string(_player->get_component<HealthComponent>().value()), &player_stats_values);
	player_stats_values.add_object<Text>("10");
	_player_stats->show();
}

Game::~Game()
{
}

void Game::action()
{
	_enemy_spawner->action();
	_player->action();
	_player_projectiles.action();
	for (auto&& enemy : _enemies) {
		enemy->action();
	}
	_enemies_projectiles.action();
}

void Game::update()
{
	for (auto&& player_projectile : _player_projectiles) {
		for (auto&& enemy_projectile : _enemies_projectiles) {
			if (!player_projectile->is_destroyed() &&
				!enemy_projectile->is_destroyed() &&
				is_collide(*player_projectile, *enemy_projectile)) {
  				player_projectile->on_collide(enemy_projectile->get_component<ColliderComponent>());
				enemy_projectile->on_collide(player_projectile->get_component<ColliderComponent>());
			}
		}
	}
	
	for (auto&& projectile : _player_projectiles) {
		for (auto&& enemy : _enemies) {
			if (enemy->has_component<ColliderComponent>() && !enemy->is_destroyed() &&
				projectile->has_component<ColliderComponent>() && !projectile->is_destroyed() &&
				is_collide(*enemy, *projectile)) {
				enemy->on_collide(projectile->get_component<ColliderComponent>());
				projectile->on_collide(enemy->get_component<ColliderComponent>());
			}
		}
	}

	for (auto&& projectile : _enemies_projectiles) {
		if (_player->has_component<ColliderComponent>() && !_player->is_destroyed() &&
			projectile->has_component<ColliderComponent>() && !projectile->is_destroyed() &&
			is_collide(*_player, *projectile)) {
			_player->on_collide(projectile->get_component<ColliderComponent>());
			projectile->on_collide(_player->get_component<ColliderComponent>());
		}
	}

	{
		decltype(auto) player_health_component = _player->get_component<HealthComponent>();
		if (player_health_component.is_changed()) {
			decltype(auto) player_stats_values = static_cast<VerticalLayout*>((*_player_stats)[1].get());
			decltype(auto) player_health_value_text = static_cast<Text*>((*player_stats_values)[1].get());
			player_health_value_text->set_text(std::to_string(player_health_component.value()));
		}
	}

	Map::update();
	_player->update();
	_active = !_player->is_destroyed();
	_player_projectiles.update();
	for (auto&& enemy : _enemies) {
		enemy->update();
	}
	_enemies.remove_if([](const std::unique_ptr<Enemy>& enemy) {return enemy->is_destroyed(); });
	_enemies_projectiles.update();
}

void Game::render()
{
}

bool Game::is_active()
{
	return _active;
}
