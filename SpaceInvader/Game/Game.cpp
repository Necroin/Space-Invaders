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
	_player_stats = std::make_unique<HorizontalLayout>(Map::frame_x() + Map::frame_width() + 1, Map::frame_y() + 1);
	decltype(auto) player_stats_names = _player_stats->add_object<VerticalLayout>(_player_stats.get());
	player_stats_names.add_object<Text>("Scrore : ");
	//player_stats_names.add_object<Text>("Money : ");
	player_stats_names.add_object<Text>("Health : ");
	player_stats_names.add_object<Text>("Weapon : ");
	player_stats_names.add_object<Text>("Attack : ");
	player_stats_names.set_model(VerticalLayout::Model::left);
	decltype(auto) player_stats_values = _player_stats->add_object<VerticalLayout>(_player_stats.get());
	decltype(auto) player_score_text = player_stats_values.add_object<Text>("0", &player_stats_values);
	//decltype(auto) player_money_text = player_stats_values.add_object<Text>("0", &player_stats_values);
	decltype(auto) player_hp_text = player_stats_values.add_object<Text>("", &player_stats_values);
	decltype(auto) player_current_weapon_text = player_stats_values.add_object<Text>("", &player_stats_values);
	decltype(auto) player_damage_text = player_stats_values.add_object<Text>("", &player_stats_values);
	

	/*player_money_changed += createLambdaEventHandler([&text = player_money_text](int new_value) {
		text.set_text(std::to_string(new_value));
		});*/

	score_changed += createLambdaEventHandler([&text = player_score_text](int new_value) {
		text.set_text(std::to_string(new_value));
		});


	_menu_buttons = std::make_unique<VerticalLayout>(Map::frame_x() + Map::frame_width() + 10, Map::frame_y() + 3, 0);
	_menu_buttons->add_object<PushButton>("Play", _menu_buttons.get()).pressed() += createLambdaEventHandler([
		&game_state = _game_state,
		&player = _player,
		&enemies = _enemies,
		&player_projectiles = _player_projectiles,
		&enemies_projectiles = _enemies_projectiles,
		&enemy_spawner = _enemy_spawner,
		&player_hp_text = player_hp_text,
		&player_current_weapon_text = player_current_weapon_text,
		&player_damage_text = player_damage_text
	]
	()
		{
			game_state = GameState::Play;
			score = 0;
			score_changed(score);
			player = std::make_unique<Player>(player_projectiles);
			enemies_projectiles.data().clear();
			enemies.clear();
			enemy_spawner = std::make_unique<EnemySpawner>(enemies_projectiles, enemies);
			player_hp_text.set_text(std::to_string(player->get_component<HealthComponent>().value()));
			player_current_weapon_text.set_text(player->curent_weapon().name());
			player_damage_text.set_text(std::to_string(player->curent_weapon().damage()));

			player->get_component<HealthComponent>().changed_event() += createLambdaEventHandler([&text = player_hp_text](int new_hp) {
				text.set_text(std::to_string(new_hp));
				});;
			player->weapon_changed_event() += createLambdaEventHandler([&damage_text = player_damage_text, &weapon_text = player_current_weapon_text](std::string& weapon_name, int new_damage) {
				damage_text.set_text(std::to_string(new_damage));
				weapon_text.set_text(weapon_name);
				});
		});
	_menu_buttons->add_object<PushButton>("Close the game", _menu_buttons.get()).pressed() += createLambdaEventHandler([&active = _active]() {
		active = false;
		});


	decltype(auto) menu_state = _game_fsm.add_state([&game = *this]() {
		game.menu();
		});

	decltype(auto) play_state = _game_fsm.add_state([&game = *this](){
		game.action();
		game.update();
		game.render();
	});

	_game_fsm.set_current_state(menu_state);
	_game_state = GameState::Menu;

	menu_state.add_transition([&play_state = play_state, &player_stats = _player_stats, &menu_buttons = _menu_buttons](GameState& state)->decltype(&menu_state) {
		if (state == GameState::Play) { 
			menu_buttons->hide();
			player_stats->show();
			return &play_state; }
		return nullptr;
		});

	play_state.add_transition([&menu_state = menu_state, &player_stats = _player_stats, &menu_buttons = _menu_buttons](GameState& state)->decltype(&play_state) {
		if (state == GameState::Menu) {
			player_stats->hide();
			menu_buttons->show();
			return &menu_state;
		}
		return nullptr;
		});

	_menu_buttons->show();
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

	Map::update();
	_player->update();
	if(_player->is_destroyed()) _game_state = GameState::Menu;
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

void Game::menu()
{
	_menu_buttons->event();
}

void Game::run()
{
	_game_fsm.handle(_game_state);
	_game_fsm.execute();
}

bool Game::is_active()
{
	return _active;
}
