#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "../Entity.h"
#include "../../Components/Base/Timer/Timer.h"
#include "../../Projectile/Projectile.h"

class Player : public Entity
{
protected:
	class AttackMainBodyElement : public MainBodyElement<Player>, public AutoResetReferenceTimer
	{
	protected:
		Map& _map;
		int& _projectile_action_delay_time;
	public:
		AttackMainBodyElement(Player& parent, Map& map, int& projectile_action_delay_time, int& fire_delay_time, int x, int y, char symbol, int color = Color::White);
		virtual void action() override;
	};

	friend class MainBodyElement<Player>;
	friend class AttackPlayerElement;

private:
	struct Parameters
	{
		static const int HP = 100;
		static const int damage = 10;
	};
	Body<MainBodyElement<Player>> _main_body;
	AutoResetTimer _input_delay_timer;
	inline static const size_t _input_dalay_time = 100;
	ProjectileList _projectiles;
	int _fire_delay_time = 100;
	int _projectile_action_delay_time = 20;
public:
	Player(Map& map);
	~Player();
public:
	void action(std::list<std::unique_ptr<Entity>>& enemies);
	void update();
	virtual bool damage_this(const Projectile& projectile) const override;
};
#endif