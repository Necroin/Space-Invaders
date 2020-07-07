#include "Entity.h"

Entity::Entity(Map& map, int HP, int x, int y) :
	_map(map),
	HealthComponent(HP),
	Coordinates(x, y)
{}