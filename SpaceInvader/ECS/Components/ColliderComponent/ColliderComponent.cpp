#include "ColliderComponent.h"
#include "../PositionComponent/PositionComponent.h"
#include "../../../Body/MechBody.h"
#include "../../../Projectile/Projectile.h"

ColliderComponent::ColliderComponent(ObjectTag tag) : _tag(tag) {}

ObjectTag ColliderComponent::tag() const { return _tag; }

Component* ColliderComponent::copy() const
{
	return new ColliderComponent(_tag);
}

bool is_collide(const MechBody& one, const MechBody& other)
{
	return false;
}

bool is_collide(const MechBody& body, const Projectile& projectile)
{
	for (auto&& body_element : body._body) {
		if (body_element->has_component<PositionComponent>() && 
			(body_element->get_component<PositionComponent>() == projectile.get_component<PositionComponent>())) {
			return true;
		}
	}
	return false;
}

bool is_collide(const Projectile& one, const Projectile& other)
{
	return one.get_component<PositionComponent>() == other.get_component<PositionComponent>();
}
