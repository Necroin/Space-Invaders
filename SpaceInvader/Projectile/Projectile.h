#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../ECS/Components/Base/Timer/Timer.h"
#include "../Map/Map.h"
#include <list> 

class Projectile : public Entity, public AutoResetTimer<>
{
public:
	Projectile(DamageComponent::damage_function_type damage, int delay_time, int x, int y, int symbol, int color = VisibleComponent::Color::White) :
		AutoResetTimer<>(delay_time)
	{
		this->add_component<PositionComponent>(x, y);
		this->add_component<DamageComponent>(damage);
		this->add_component<VisibleComponent>(symbol, color).show();
	}
};

class ProjectileList : public GroupMoveComponent<std::list<Projectile>>, public GroupVisibleComponent<std::list<Projectile>> {
public:
	void add_projectile(DamageComponent::damage_function_type damage, int delay_time, int x, int y, int symbol, int color = VisibleComponent::Color::White) {
		_container.emplace_back(damage, delay_time, x, y, symbol, color);
	}
};
#endif