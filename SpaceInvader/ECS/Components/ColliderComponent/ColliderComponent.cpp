#include "ColliderComponent.h"
#include "../PositionComponent/PositionComponent.h"
#include "../../../Body/Body.h"
#include "../../../Body/MechBody.h"

bool is_collide(const MechBody& one, const MechBody& other)
{
	return false;
}

bool is_collide(const MechBody& one, const Body& other)
{
	return false;
}

bool is_collide(const Body& one, const MechBody& other)
{
	return false;
}

bool is_collide(const Body& one, const Body& other)
{
	if (one.has_component<PositionComponent>() && other.has_component<PositionComponent>()) {
		return one.get_component<PositionComponent>() == other.get_component<PositionComponent>();
	}
	return false;
}

