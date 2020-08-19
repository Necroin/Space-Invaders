#include "Projectile.h"
#include "../Enemy/Enemy.h"

Projectile::Projectile(
	DamageComponent::damage_function_type damage,
	int delay_time,
	int x,
	int y,
	const PositionComponent::Direction& direction,
	int symbol,
	int color
)
	:
	AutoResetTimer<>(delay_time)
{
	this->add_component<PositionComponent>(x, y, direction.horizontal_direction, direction.vertical_direction);
	this->add_component<DamageComponent>(damage);
	this->add_component<VisibleComponent>(symbol, color).show();
	this->add_component<ColliderComponent>(ObjectTag::Projectile);
}

Projectile::~Projectile()
{
	this->get_component<VisibleComponent>().hide();
}

bool Projectile::action()
{
	return true;
}

bool Projectile::update()
{
	return !this->is_destroyed();
}

void Projectile::on_collide(const ColliderComponent& collider_component)
{
	if (collider_component.tag() == ObjectTag::Enemy) {
		decltype(auto) entity = collider_component.entity();
		if (entity.has_component<HealthComponent>() &&
			!entity.get_component<HealthComponent>().apply_damage(this->get_component<DamageComponent>())) {
			entity.destroy();
			score += static_cast<Enemy&>(entity).scrore_reward();
			score_changed(score);
			player_money += static_cast<Enemy&>(entity).money_reward();
			player_money_changed(player_money);
		}
	}
	if (collider_component.tag() == ObjectTag::Player) {
		decltype(auto) entity = collider_component.entity();
		if (entity.has_component<HealthComponent>() &&
			!entity.get_component<HealthComponent>().apply_damage(this->get_component<DamageComponent>())) {
			entity.destroy();
		}
	}
	if (collider_component.tag() == ObjectTag::Projectile) {
		collider_component.entity().destroy();
	}
}

void ProjectileList::action()
{
	decltype(auto) projectile_iterator = _container.begin();
	while (projectile_iterator != _container.end()) {
		decltype(auto) projectile = *projectile_iterator;
		if (!projectile->action()) {
			decltype(auto) delete_projectile_iterator = projectile_iterator;
			++projectile_iterator;
			_container.erase(delete_projectile_iterator);
		}
		else {
			++projectile_iterator;
		}
	}
}

void ProjectileList::update()
{
	decltype(auto) projectile_iterator = _container.begin();
	while (projectile_iterator != _container.end()) {
		decltype(auto) projectile = *projectile_iterator;
		if (!projectile->update()) {
			decltype(auto) delete_projectile_iterator = projectile_iterator;
			++projectile_iterator;
			_container.erase(delete_projectile_iterator);
		}
		else {
			++projectile_iterator;
		}
	}
}
