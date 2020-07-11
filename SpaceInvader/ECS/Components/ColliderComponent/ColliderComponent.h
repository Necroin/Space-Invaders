#pragma once
#ifndef _COLLIDERCOMPONENT_H_
#define _COLLIDERCOMPONENT_H_
#include "../../ECS.h"

enum class ObjectTag {
	Player,
	Enemy,
	Projectile
};

class ColliderComponent : public Component 
{
private:
	ObjectTag _tag;
public:
	ColliderComponent(ObjectTag tag) : _tag(tag) {}
	ObjectTag tag() { return _tag; }
};

class Body;
class MechBody;

bool is_collide(const MechBody& one, const MechBody& other);
bool is_collide(const MechBody& one, const Body& other);
bool is_collide(const Body& one, const MechBody& other);
bool is_collide(const Body& one, const Body& other);
#endif