#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../ECS/Components/Base/Timer/Timer.h"
#include "../Map/Map.h"
#include <list> 

class Projectile : 
	public Entity, 
	public AutoResetTimer<>
{
protected:
	Map& _map;
public:
	Projectile(Map& map, DamageComponent::damage_function_type damage, int delay_time, int x, int y, int forward_direction, int symbol, int color = VisibleComponent::Color::White);
	~Projectile();
	virtual bool action();
	virtual bool update();
};

class ProjectileList : 
	public GroupMoveComponent<std::list<std::unique_ptr<Projectile>>>,
	public GroupVisibleComponent<std::list<std::unique_ptr<Projectile>>> {
public:
	template<class _Projectile >
	void add_projectile(Map& map, DamageComponent::damage_function_type damage, int delay_time, int x, int y, int forward_direction, int symbol, int color = VisibleComponent::Color::White) {
		_container.emplace_back(std::make_unique<_Projectile>(map, damage, delay_time, x, y, forward_direction, symbol, color));
	}
};
#endif