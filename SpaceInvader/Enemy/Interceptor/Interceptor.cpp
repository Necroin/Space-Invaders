#include "Interceptor.h"

Interceptor::Interceptor(Map& map, ProjectileList& projectiles, int x, int y) :
	_map(map),
	_projectiles(projectiles)
{
	_body.add_element<AttackBodyElement>(_map, _projectiles).
		add_component<PositionComponent>(x,y, PositionComponent::Direction::left).
		add_component<VisibleComponent>('<', VisibleComponent::Color::Red);
	_body.show();
}

void Interceptor::action()
{
	_body.action();
}

void Interceptor::update()
{
	_body.update();
	_body.show();
}

Interceptor::AttackBodyElement::AttackBodyElement(Map& map, ProjectileList& projectiles) : 
	_weapon(*this, map, projectiles, 500, PositionComponent::Direction::left, VisibleComponent::Color::Red) {}

void Interceptor::AttackBodyElement::action()
{
	if (!_weapon.tick()) {
		_weapon.shoot();
	}
	_weapon.action();
}

void Interceptor::AttackBodyElement::update()
{
	_weapon.update();
}