#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../Base/Timer/Timer.h"
#include "../Map/Map.h"
#include "../Data/Data.h"
#include <list> 

class Projectile : 
	public Entity, 
	public AutoResetTimer<>
{
protected:
public:
	Projectile(
		DamageComponent::damage_function_type damage, 
		int delay_time, 
		int x, 
		int y, 
		const PositionComponent::Direction& direction,
		int symbol, 
		int color = VisibleComponent::Color::White
	);
	~Projectile();
	virtual bool action();
	virtual bool update();
	virtual void on_collide(const ColliderComponent& collider_component);
};

class ProjectileList :
	public GroupMoveComponent<std::list<std::unique_ptr<Projectile>>>,
	public GroupVisibleComponent<std::list<std::unique_ptr<Projectile>>>
{
public:
	template<class _Projectile>
	void add_projectile(
		DamageComponent::damage_function_type damage,
		int delay_time,
		int x,
		int y,
		const PositionComponent::Direction& direction,
		int symbol,
		int color = VisibleComponent::Color::White
	)
	{
		_container.emplace_back(std::make_unique<_Projectile>(
			damage,
			delay_time,
			x,
			y,
			direction,
			symbol,
			color
			)
		);
	}

	void action();
	void update();
};
#endif