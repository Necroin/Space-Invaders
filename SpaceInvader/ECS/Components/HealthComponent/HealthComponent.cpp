#include "HealthComponent.h"

HealthComponent::HealthComponent(int health, int shield) :
	_health(health),
	_shield(shield)
{}

bool HealthComponent::apply_damage(const DamageComponent& damage_component)
{
	return damage_component(_health, _shield);
}

Component* HealthComponent::copy() const
{
	return new HealthComponent(_health, _shield);
}
