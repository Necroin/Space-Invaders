#include "HealthComponent.h"

HealthComponent::HealthComponent(int health, int shield) :
	_health(health),
	_shield(shield)
{}

bool HealthComponent::apply_damage(const DamageComponent& damage_component)
{
	_changed = true;
	return damage_component(_health, _shield);
}

Component* HealthComponent::copy() const
{
	return new HealthComponent(_health, _shield);
}

bool HealthComponent::is_changed()
{
	return _changed;
}

int HealthComponent::value()
{
	return _health;
}

void HealthComponent::update()
{
	_changed = false;
}
