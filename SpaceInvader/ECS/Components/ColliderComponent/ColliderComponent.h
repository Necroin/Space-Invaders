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
	ColliderComponent(ObjectTag tag);
	ObjectTag tag() const;
	virtual Component* copy() const override;
};

class MechBody;
class Projectile;

bool is_collide(const MechBody& one, const MechBody& other);
bool is_collide(const MechBody& body, const Projectile& projectile);
bool is_collide(const Projectile& one, const Projectile& other);

#endif