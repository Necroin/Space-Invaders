#include "Railgun.h"
#include "../../WinAPI/WinAPI.h"
#include "../../ECS/Components/PositionComponent/PositionComponent.h"

Railgun::Railgun(Entity& parent, Map& map, ProjectileList& projectiles, int fire_delay, int forward_direction, int color) :
	Weapon(map, projectiles, fire_delay),
	_parent(parent),
	_color(color),
	_forward_direction(forward_direction)
{}

void Railgun::shoot()
{
	if (_parent.has_component<PositionComponent>()) {
		decltype(auto) position_component = _parent.get_component<PositionComponent>();
		if ((position_component.x() < (_map.position().x + _map.position().width - 1)) && (position_component.x() >= _map.position().x)) {
			_projectiles.add_projectile<RailgunProjectile>(
				_map,
				default_damage(10),
				_projectile_action_delay_time,
				position_component.forward_x(),
				position_component.forward_y(),
				_forward_direction,
				'=',
				_color
				);
		}
	}
}

Railgun::RailgunProjectile::RailgunProjectile(Map& map, DamageComponent::damage_function_type damage, int delay_time, int x, int y, int forward_direction, int symbol, int color) :
	Projectile(map,damage,delay_time, x, y, forward_direction, symbol, color)
{}

bool Railgun::RailgunProjectile::action()
{
	if (!tick()) {
		decltype(auto) projectile_visible_coponent = this->get_component<VisibleComponent>();
		decltype(auto) projectile_position_coponent = this->get_component<PositionComponent>();
		projectile_visible_coponent.hide();
		projectile_position_coponent.move_forward();
		if (projectile_position_coponent.x() > (_map.position().x + _map.position().width - 1) || projectile_position_coponent.x() < _map.position().x) {
			return false;
		}
		else {
			projectile_visible_coponent.show();
		}
	}

	return true;
}

