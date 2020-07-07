#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "../Components/DamageComponent/DamageComponent.h"
#include "../Components/MoveComponent/GroupMoveComponent.h"
#include "../Components/VisibleComponent/GroupVisibleComponent.h"
#include "../Components/DestroyedComponent/DestroyedComponent.h"
#include "../Components/Base/Timer/Timer.h"
#include "../Map/Map.h"
#include <list> 

class Projectile : public DamageComponent, public MoveComponent, public VisibleComponent, public AutoResetTimer, public DestroyedComponent {
public:
	Projectile(DamageComponent::damage_type damage, int delay_time, int x, int y, int symbol, int color = Color::White) :
		DamageComponent(damage),
		MoveComponent(x, y),
		VisibleComponent(x, y, symbol, color),
		Coordinates(x, y),
		AutoResetTimer(delay_time)
	{
		show();
	}
	~Projectile() {
		hide();
	}
};

class ProjectileList : public GroupMoveComponent<std::list<Projectile>>, public GroupVisibleComponent<std::list<Projectile>> {
public:
	void add_projectile(DamageComponent::damage_type damage, int delay_time, int x, int y, int symbol, int color = VisibleComponent::Color::White) {
		_container.emplace_back(damage, delay_time, x, y, symbol, color);
	}

	void clear_destroyed() {
		_container.remove_if(
			[](const Projectile& projectile) {
				return projectile.is_destroyed();
			}
		);
	}
};
#endif