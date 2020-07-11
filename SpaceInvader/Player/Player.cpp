#include "Player.h"
#include "../../WinAPI/WinAPI.h"
Player::Player(Map& map, ProjectileList& projectiles) :
	_map(map),
	_projectiles(projectiles),
	_input_delay_timer(_input_dalay_time)
{
	auto map_position = _map.position();
	decltype(auto) position_component = this->add_component<PositionComponent>(map_position.x + 1, (map_position.y + map_position.height) / 2);
	decltype(auto) health_component = this->add_component<HealthComponent>(Parameters::HP);
	auto [x, y] = position_component.coordinates();

	decltype(auto) attack_eleent = _body.add_element<AttackBodyElement>(_current_weapon).
		add_component<PositionComponent>(x + 2, y).
		add_component<VisibleComponent>('>', VisibleComponent::Color::Green).entity();

	_railgun = new Railgun(attack_eleent, _projectiles);
	_current_weapon = _railgun;

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x, y).
		add_component<VisibleComponent>('=', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x + 1, y).
		add_component<VisibleComponent>('=', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x, y - 1).
		add_component<VisibleComponent>('\\', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x + 1, y - 1).
		add_component<VisibleComponent>('\\', VisibleComponent::Color::Green);
	
	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x, y + 1).
		add_component<VisibleComponent>('/', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x + 1, y + 1).
		add_component<VisibleComponent>('/', VisibleComponent::Color::Green);

	_body.show();
}

Player::~Player()
{
	if(_railgun) delete _railgun;
}

void Player::action()
{
	auto map_position = _map.position();
	decltype(auto) player_position_component = this->get_component<PositionComponent>();
	auto [x, y] = player_position_component.coordinates();
	if (!_input_delay_timer.tick()) {
		_body.hide();
		if (GetAsyncKeyState(0x57) && ((y - 1) > map_position.y)) {
			player_position_component.move_up();
			_body.move_up();
		}
		if (GetAsyncKeyState(0x53) && ((y + 1) < (map_position.y + map_position.height - 1))) {
			_body.move_down();
			player_position_component.move_down();
		}
		if (GetAsyncKeyState(0x41) && (x > map_position.x)) {
			_body.move_left();
			player_position_component.move_left();
		}
		if (GetAsyncKeyState(0x44) && (x < (map_position.x + map_position.width - 3))) {
			_body.move_right();
			player_position_component.move_right();
		}
	}
	_body.action();


	auto projectiles_iterator = _projectiles.begin();
	while (projectiles_iterator != _projectiles.end()) {
		decltype(auto) projectile = *projectiles_iterator;
		if (!projectile.tick()) {
			decltype(auto) projectile_visible_coponent = projectile.get_component<VisibleComponent>();
			decltype(auto) projectile_position_coponent = projectile.get_component<PositionComponent>();
			projectile_visible_coponent.hide();
			projectile_position_coponent.move_right();
			if (projectile_position_coponent.x() >= (map_position.x + map_position.width - 1)) {
				auto delete_projectile_iterator = projectiles_iterator;
				++projectiles_iterator;
				_projectiles.data().erase(delete_projectile_iterator);
			}
			else {
				++projectiles_iterator;
				projectile_visible_coponent.show();
			}
		}
		else {
			++projectiles_iterator;
		}
	}
}

void Player::update()
{
	_body.update();
	_body.show();
}


void Player::AttackBodyElement::action()
{
	if (_weapon) _weapon->action();
}

void Player::AttackBodyElement::update()
{
	if (_weapon) _weapon->update();
}
