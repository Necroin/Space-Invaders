#include "PositionComponent.h"

PositionComponent::PositionComponent(int x, int y, int forward_direction):
	_x(x),
	_y(y),
	_forward_direction(forward_direction)
{}

int PositionComponent::x()
{
	return _x;
}

int PositionComponent::forward_x()
{
	if (_forward_direction == Direction::left) return _x - 1;
	if (_forward_direction == Direction::right) return _x + 1;
	return _x;
}

int PositionComponent::forward_y()
{
	if (_forward_direction == Direction::up) return _y - 1;
	if (_forward_direction == Direction::down) return _y + 1;
	return _y;
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

void PositionComponent::move_forward()
{
	(this->*_direction_move[_forward_direction])();
}

bool PositionComponent::operator==(const PositionComponent& other)
{
	return _x == other._x && _y == other._y;
}

bool PositionComponent::operator!=(const PositionComponent& other)
{
	return !(*this == other);
}

Component* PositionComponent::copy() const
{
	return new PositionComponent(_x, _y, _forward_direction);
}
