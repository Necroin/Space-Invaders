#include "Coordinates.h"

Coordinates::Coordinates(int x, int y) : _x(x), _y(y)
{}

std::pair<int, int> Coordinates::coordinates()
{
	return std::pair<int, int>(_x, _y);
}
