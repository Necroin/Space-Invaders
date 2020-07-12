#include "Player.h"
#include "../../WinAPI/WinAPI.h"

Player::Player(Map& map, ProjectileList& projectiles) :
	_map(map),
	_projectiles(projectiles),
	_input_delay_timer(_input_dalay_time)
{
	auto map_position = _map.position();
	decltype(auto) position_component = this->add_component<PositionComponent>(
		map_position.x + 1, 
		(map_position.y + map_position.height) / 2, 
		PositionComponent::Direction::right
		);
	decltype(auto) health_component = this->add_component<HealthComponent>(Parameters::HP);
	auto [x, y] = position_component.coordinates();
	this->add_component<ColliderComponent>(ObjectTag::Player);

	decltype(auto) attack_eleent = _body.add_element<AttackBodyElement>(_current_weapon).
		add_component<PositionComponent>(x + 2, y, PositionComponent::Direction::right).
		add_component<VisibleComponent>('>', VisibleComponent::Color::Green).entity();

	_railgun = new Railgun(attack_eleent, _map, _projectiles, 100, PositionComponent::Direction::right, VisibleComponent::Color::Green);
	_current_weapon = _railgun;

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x, y, PositionComponent::Direction::right).
		add_component<VisibleComponent>('=', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x + 1, y, PositionComponent::Direction::right).
		add_component<VisibleComponent>('=', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x, y - 1, PositionComponent::Direction::right).
		add_component<VisibleComponent>('\\', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x + 1, y - 1, PositionComponent::Direction::right).
		add_component<VisibleComponent>('\\', VisibleComponent::Color::Green);
	
	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x, y + 1, PositionComponent::Direction::right).
		add_component<VisibleComponent>('/', VisibleComponent::Color::Green);

	_body.add_element<BodyElement>().
		add_component<PositionComponent>(x + 1, y + 1, PositionComponent::Direction::right).
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
}

void Player::update()
{
	_body.update();
	_body.show();
}

void Player::AttackBodyElement::action()
{
	if (GetAsyncKeyState(VK_SPACE) && !_weapon->tick()) {
		_weapon->shoot();
	}
	if (_weapon) _weapon->action();
}

void Player::AttackBodyElement::update()
{
	if (_weapon) _weapon->update();
}
