#include "PositionComponent.h"

PositionComponent::PositionComponent(int x, int y): 
	_x(x),
	_y(y)
{}

int PositionComponent::x()
{
	return _x;
}

int PositionComponent::y()
{
	return _y;
}

std::pair<int, int> PositionComponent::coordinates()
{
	return { _x, _y };
}

void PositionComponent::move_left()
{
	--_x;
}

void PositionComponent::move_right()
{
	++_x;
}

void PositionComponent::move_up()
{
	--_y;
}

void PositionComponent::move_down()
{
	++_y;
}

void PositionComponent::move_to(int x, int y)
{
	_x = x;
	_y = y;
}

bool PositionComponent::operator==(const PositionComponent& other)
{
	return _x == other._x && _y == other._y;
}

bool PositionComponent::operator!=(const PositionComponent& other)
{
	return !(*this == other);
}

Component* PositionComponent::copy()
{
	return new PositionComponent(_x, _y);
}
