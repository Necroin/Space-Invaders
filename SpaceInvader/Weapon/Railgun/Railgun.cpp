#include "Railgun.h"
#include "../../WinAPI/WinAPI.h"
#include "../../ECS/Components/PositionComponent/PositionComponent.h"

Railgun::Railgun(
	Entity& parent, 
	ProjectileList& projectiles, 
	int fire_delay,
	int damage,
	int color
)
	:
	Weapon(projectiles, fire_delay, damage),
	_parent(parent),
	_color(color)
{}

void Railgun::shoot()
{
	if (_parent.has_component<PositionComponent>()) {
		decltype(auto) position_component = _parent.get_component<PositionComponent>();
		if (Map::in_map(position_component.forward_x(), position_component.forward_y())) {
			_projectiles.add_projectile<RailgunProjectile>(
				default_damage(_damage),
				_projectile_action_delay_time,
				position_component.forward_x(),
				position_component.forward_y(),
				position_component.direction(),
				'=',
				_color
				);
		}
	}
}

std::string& Railgun::name() const
{
	return _name;
}

Railgun::RailgunProjectile::RailgunProjectile(
	DamageComponent::damage_function_type damage,
	int delay_time,
	int x,
	int y,
	const PositionComponent::Direction& direction,
	int symbol,
	int color
) 
	:
	Projectile(damage,delay_time, x, y, direction, symbol, color)
{}

bool Railgun::RailgunProjectile::action()
{
	if (!tick()) {
		decltype(auto) projectile_visible_coponent = this->get_component<VisibleComponent>();
		decltype(auto) projectile_position_coponent = this->get_component<PositionComponent>();
		projectile_visible_coponent.hide();
		projectile_position_coponent.move_forward();
		if (!Map::in_map(projectile_position_coponent.x(), projectile_position_coponent.y())) {
			return false;
		}
		else {
			projectile_visible_coponent.show();
		}
	}

	return true;
}

