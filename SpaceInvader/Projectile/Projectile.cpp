#include "Projectile.h"

Projectile::Projectile(Map& map, DamageComponent::damage_function_type damage, int delay_time, int x, int y, int forward_direction, int symbol, int color) :
	AutoResetTimer<>(delay_time),
	_map(map)
{
	this->add_component<PositionComponent>(x, y, forward_direction);
	this->add_component<DamageComponent>(damage);
	decltype(auto) visible_component = this->add_component<VisibleComponent>(symbol, color);
	this->add_component<ColliderComponent>(ObjectTag::Projectile);
	if (x < (_map.position().x + _map.position().width) && x >= _map.position().x) {
		visible_component.show();
	}
}

Projectile::~Projectile()
{
	if (this->get_component<PositionComponent>().x() < (_map.position().x + _map.position().width) && 
		this->get_component<PositionComponent>().x() >= _map.position().x) {
		this->get_component<VisibleComponent>().hide();
	}
}

bool Projectile::action()
{
	return true;
}

bool Projectile::update()
{
	return !this->is_destroyed();
}
