#include "Enemy.h"

bool Enemy::damage_this(const Projectile& projectile)
{
	bool result = 1;
	for (auto&& element : _main_body) {
		if (static_cast<Coordinates&>(*element) == static_cast<const Coordinates&>(projectile)) {
			result *= element->damage_this(projectile);
		}
	}
	return result;
}
