#include "HealthComponent.h"

HealthComponent::HealthComponent(int health, int shield) :
	_health(health),
	_shield(shield)
{}

bool HealthComponent::apply_damage(const DamageComponent& damage_component)
{
	bool result = damage_component(_health, _shield);
	_changed_event(_health);
	return result;
}

Component* HealthComponent::copy() const
{
	return new HealthComponent(_health, _shield);
}

int HealthComponent::value()
{
	return _health;
}

IEvent<int>& HealthComponent::changed_event()
{
	return _changed_event;
}
