#include "DamageComponent.h"

DamageComponent::DamageComponent(damage_function_type damage_function) : _damage_function(damage_function) {}

bool DamageComponent::operator()(int& health_points, int& shield) const
{
	return _damage_function(health_points, shield);
}

Component* DamageComponent::copy() const
{
	return new DamageComponent(_damage_function);
}
