#include "Enemy.h"

Enemy::~Enemy() {}

void Enemy::on_collide(const ColliderComponent& collider_component)
{
	if (collider_component.tag() == ObjectTag::Projectile) {
		collider_component.entity().destroy();
	}
}
