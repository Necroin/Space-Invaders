#include "Player.h"
#include "../../WinAPI/WinAPI.h"
Player::Player(Map& map) :
	Entity(map, Parameters::HP, map.position().x, (map.position().y + map.position().height) / 2), 
	_input_delay_timer(_input_dalay_time)
{
	_x;
	_y;
	_main_body.add_element<MainBodyElement<Player>>(*this, _x, _y, '=', VisibleComponent::Color::Green);
	_main_body.add_element<MainBodyElement<Player>>(*this, _x + 1, _y, '=', VisibleComponent::Color::Green);
	_main_body.add_element<AttackMainBodyElement>(*this, _map, _projectile_action_delay_time, _fire_delay_time , _x + 2, _y, '>', VisibleComponent::Color::Green);

	_main_body.add_element<MainBodyElement<Player>>(*this, _x, _y - 1, '\\', VisibleComponent::Color::Green);
	_main_body.add_element<MainBodyElement<Player>>(*this, _x + 1, _y - 1, '\\', VisibleComponent::Color::Green);
	
	_main_body.add_element<MainBodyElement<Player>>(*this, _x, _y + 1, '/', VisibleComponent::Color::Green);
	_main_body.add_element<MainBodyElement<Player>>(*this, _x + 1, _y + 1, '/', VisibleComponent::Color::Green);

	_main_body.show();
}

Player::~Player()
{
}

void Player::action(std::list<std::unique_ptr<Entity>>& enemies)
{
	auto map_position = _map.position();
	if (!_input_delay_timer.tick()) {
		_main_body.hide();
		if (GetAsyncKeyState(0x57) && ((_y - 1) > map_position.y)) {
			--_y;
			_main_body.move_up();
		}
		if (GetAsyncKeyState(0x53) && ((_y + 1) < (map_position.y + map_position.height - 1))) {
			_main_body.move_down();
			++_y;
		}
		if (GetAsyncKeyState(0x41) && (_x > map_position.x)) {
			_main_body.move_left();
			--_x;
		}
		if (GetAsyncKeyState(0x44) && (_x < (map_position.x + map_position.width - 3))) {
			_main_body.move_right();
			++_x;
		}
	}
	_main_body.action();

	auto projectiles_iterator = _projectiles.begin();
	while (projectiles_iterator != _projectiles.end()) {
		decltype(auto) projectile = *projectiles_iterator;
		if (!projectile.tick()) {
			projectile.hide();
			projectile.move_right();
			auto [x, y] = projectile.coordinates();
			if (x >= (map_position.x + map_position.width - 1)) {
				auto delete_projectile_iterator = projectiles_iterator;
				++projectiles_iterator;
				_projectiles.data().erase(delete_projectile_iterator);
			}
			else {
				++projectiles_iterator;
				projectile.show();
			}
		}
		else {
			++projectiles_iterator;
		}
	}
	/*bool need_clear_destroyed = false;
	for (auto&& projectile : _projectiles) {
		if (!projectile.tick()) {
			projectile.move_right();
			for (auto&& enemy : enemies) {
				if (projectile.is_destroyed()) {
					break;
				}
				if (!enemy->is_destroyed() && static_cast<Coordinates&>(*enemy) == static_cast<Coordinates&>(*this)) {
					enemy->damage_this(projectile.damage());
					projectile.destroy();
				}
			}
			
		}
	}
	if (need_clear_destroyed) { _projectiles.clear_destroyed(); }*/
	
}

void Player::update()
{
	_main_body.update();
	_main_body.show();
}

bool Player::damage_this(const Projectile& projectile) const
{
	bool result = true;
	
	return result;
}

Player::AttackMainBodyElement::AttackMainBodyElement(Player& parent, Map& map, int& projectile_action_delay_time, int& fire_delay_time, int x, int y, char symbol, int color) :
	MainBodyElement<Player>(parent, x, y, symbol, color),
	Coordinates(x, y),
	AutoResetReferenceTimer(fire_delay_time),
	_map(map),
	_projectile_action_delay_time(projectile_action_delay_time)
{}

void Player::AttackMainBodyElement::action()
{
	if (GetAsyncKeyState(VK_SPACE) && !tick()) {
		_parent._projectiles.add_projectile(
			default_damage(10),
			_projectile_action_delay_time,
			_x+1,
			_y,
			'=',
			VisibleComponent::Color::Green
		);
	}
}


