#pragma once
#ifndef _COLLIDERCOMPONENT_H_
#define _COLLIDERCOMPONENT_H_
#include "../../ECS.h"

enum class ObjectTag {
	Player,
	Enemy,
	Projectile
};

/**
constructor : ColliderComponent(ObjectTag tag)
methoods :
ObjectTag tag()
*/
class ColliderComponent : public Component 
{
private:
	ObjectTag _tag;
public:
	ColliderComponent(ObjectTag tag) : _tag(tag) {}
	ObjectTag tag() { return _tag; }
	virtual Component* copy() const override;
};

class MechBody;

bool is_collide(const MechBody& one, const MechBody& other);
#endif