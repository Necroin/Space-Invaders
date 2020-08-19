#include "Enemy.h"

Enemy::~Enemy() {}

void Enemy::on_collide(const ColliderComponent& collider_component)
{
	if (collider_component.tag() == ObjectTag::Projectile) {
		collider_component.entity().destroy();
	}
}

int Enemy::money_reward() const
{
	return _money_reward;
}

int Enemy::scrore_reward() const
{
	return _scrore_reward;
}
