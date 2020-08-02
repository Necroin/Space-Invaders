#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "../Body/MechBody.h"
#include "../Weapon/Railgun/Railgun.h"
#include "../Map/Map.h"

class Player : public MechBody
{
protected:
	class AttackBodyElement : public BodyElement
	{
	protected:
		Weapon*& _weapon;
	public:
		AttackBodyElement(Weapon*& weapon) : _weapon(weapon) {}
		virtual void action() override;
		virtual void update() override;
	};
private:
	struct Parameters
	{
		static const int HP = 1000;
		static const int damage = 10;
	};
	AutoResetTimer<> _input_delay_timer;
	inline static const size_t _input_dalay_time = 100;
	Weapon* _railgun = nullptr;
	Weapon* _current_weapon = nullptr;
	ProjectileList& _projectiles;
public:
	Player(ProjectileList& projecitles);
	~Player();
public:
	void action();
	void update();
	void on_collide(const ColliderComponent& collider_component);
};
#endif