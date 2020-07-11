#include "Railgun.h"
#include "../../WinAPI/WinAPI.h"
#include "../../ECS/Components/PositionComponent/PositionComponent.h"

Railgun::Railgun(Entity& parent, ProjectileList& projectiles) :
	Weapon(projectiles),
	_parent(parent),
	_shoot_delay_timer(100)
{}

void Railgun::action()
{

	if (GetAsyncKeyState(VK_SPACE) && !_shoot_delay_timer.tick()) {
		if (_parent.has_component<PositionComponent>()) {
			decltype(auto) position_component = _parent.get_component<PositionComponent>();
			_projectiles.add_projectile(
				default_damage(10),
				_projectile_action_delay_time,
				position_component.x() + 1,
				position_component.y(),
				'=',
				VisibleComponent::Color::Green
			);
		}
	}
}

void Railgun::update()
{
}
