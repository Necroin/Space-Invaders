#include "ColliderComponent.h"
#include "../PositionComponent/PositionComponent.h"
#include "../../../Body/MechBody.h"

bool is_collide(const MechBody& one, const MechBody& other)
{
	return false;
}

Component* ColliderComponent::copy() const
{
	return new ColliderComponent(_tag);
}
