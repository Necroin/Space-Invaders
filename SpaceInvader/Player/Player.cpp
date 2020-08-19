#include "Player.h"
#include "../../WinAPI/WinAPI.h"

Player::Player(ProjectileList& projectiles) :
	_projectiles(projectiles),
	_input_delay_timer(_input_dalay_time)
{
	decltype(auto) position_component = this->add_component<PositionComponent>(
		Map::x() + 1, 
		(Map::y() + Map::height()) / 2, 
		PositionComponent::HorizontalDirection::right
		);
	decltype(auto) health_component = this->add_component<HealthComponent>(Parameters::HP);
	auto [x, y] = position_component.coordinates();
	this->add_component<ColliderComponent>(ObjectTag::Player);

	decltype(auto) attack_element = _body.add_element<AttackBodyElement>(_current_weapon).
		add_component<PositionComponent>(x + 2, y, PositionComponent::HorizontalDirection::right).
		add_component<VisibleComponent>('>', VisibleComponent::Color::Green).entity();

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

	_railgun = new Railgun(attack_element, _projectiles, 100, Parameters::damage, VisibleComponent::Color::Green);
	_current_weapon = _railgun;
	_current_weapon_damage_change_handler = createLambdaEventHandler([&weapon_change_event = _weapon_changed_event, &weapon = _current_weapon](int new_damage) {
			weapon_change_event(weapon->name(), new_damage);
	});
	_current_weapon->damage_change_event() += _current_weapon_damage_change_handler;
}

Player::~Player()
{
	if(_railgun) delete _railgun;
	_body.hide();
}

void Player::action()
{
	if (!_input_delay_timer.tick()) {
		decltype(auto) player_position_component = this->get_component<PositionComponent>();
		auto [x, y] = player_position_component.coordinates();
		_body.hide();
		if (GetAsyncKeyState(0x57) && ((y - 1) > Map::y())) {
			player_position_component.move_up();
			_body.move_up();
		}
		if (GetAsyncKeyState(0x53) && ((y + 1) < (Map::y() + Map::height() - 1))) {
			_body.move_down();
			player_position_component.move_down();
		}
		if (GetAsyncKeyState(0x41) && (x > Map::x())) {
			_body.move_left();
			player_position_component.move_left();
		}
		if (GetAsyncKeyState(0x44) && (x < (Map::x() + Map::width() - 3))) {
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
	this->get_component<HealthComponent>().update();
}

void Player::on_collide(const ColliderComponent& collider_component)
{
	if (collider_component.tag() == ObjectTag::Projectile) {
		collider_component.entity().destroy();
	}
}

IEvent<std::string&, int>& Player::weapon_changed_event()
{
	return _weapon_changed_event;
}

const Weapon& Player::curent_weapon() const
{
	return *_current_weapon;
}

void Player::AttackBodyElement::action()
{
	if (GetAsyncKeyState(VK_SPACE) && !_weapon->tick()) {
		_weapon->shoot();
	}
}

void Player::AttackBodyElement::update() {}
