#include "Interceptor.h"

Interceptor::Interceptor(ProjectileList& projectiles, int x, int y) :
	_projectiles(projectiles),
	_input_delay_timer(_input_dalay_time)
{

	this->add_component<ColliderComponent>(ObjectTag::Enemy);
	this->add_component<HealthComponent>(50);

	_body.add_element<AttackBodyElement>(_projectiles).
		add_component<PositionComponent>(x, y, PositionComponent::HorizontalDirection::left).
		add_component<VisibleComponent>('<', VisibleComponent::Color::Red);
		
	_body.show();
}

Interceptor::~Interceptor()
{
	_body.hide();
}

void Interceptor::action()
{
	if (!_input_delay_timer.tick()) {
		auto map_position = Map::position();
		decltype(auto) player_position_component = _body.data().front()->get_component<PositionComponent>();
		auto [x, y] = player_position_component.coordinates();
		std::random_device rd;
		int direction = (std::uniform_int_distribution<int>(0, 3))(rd);
		_body.hide();
		if (direction == 0 && ((y - 1) > map_position.y)) {
			player_position_component.move_up();
		}
		if (direction == 1 && ((y + 1) < (map_position.y + map_position.height - 1))) {
			player_position_component.move_down();
		}
		if (direction == 2 && (x > map_position.width - 15)) {
			player_position_component.move_left();
		}
		if (direction == 3 && (x < (map_position.x + map_position.width - 3))) {
			player_position_component.move_right();
		}
	}


	_body.action();
}

void Interceptor::update()
{
	_body.update();
	_body.show();
}

Interceptor::AttackBodyElement::AttackBodyElement(ProjectileList& projectiles) : 
	_weapon(*this, projectiles, 1000, 10, VisibleComponent::Color::Red) {}

void Interceptor::AttackBodyElement::action()
{
	if (!_weapon.tick()) {
		_weapon.shoot();
	}
}

void Interceptor::AttackBodyElement::update()
{
}