#include "PositionComponent.h"

PositionComponent::PositionComponent(int x, int y) :
	_x(x),
	_y(y),
	_horizontal_direction(HorizontalDirection::null),
	_vertical_direction(VerticalDirection::null)
{}

PositionComponent::PositionComponent(int x, int y, HorizontalDirection horizontal_direction, VerticalDirection vertical_direction) :
	_x(x),
	_y(y),
	_horizontal_direction(horizontal_direction),
	_vertical_direction(vertical_direction)
{}

PositionComponent::PositionComponent(int x, int y, VerticalDirection vertical_direction, HorizontalDirection horizontal_direction) :
	_x(x),
	_y(y),
	_horizontal_direction(horizontal_direction),
	_vertical_direction(vertical_direction)
{}

int PositionComponent::x() const noexcept
{
	return _x;
}

int PositionComponent::forward_x() const noexcept
{
	if (_horizontal_direction == HorizontalDirection::left) return _x - 1;
	if (_horizontal_direction == HorizontalDirection::right) return _x + 1;
	return _x;
}

int PositionComponent::forward_y() const noexcept
{
	if (_vertical_direction == VerticalDirection::up) return _y - 1;
	if (_vertical_direction == VerticalDirection::down) return _y + 1;
	return _y;
}

int PositionComponent::y() const noexcept
{
	return _y;
}

PositionComponent::Coordinates PositionComponent::coordinates()
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
	_x = forward_x();
	_y = forward_y();
}

void PositionComponent::set_direction(HorizontalDirection horizontal_direction)
{
	_horizontal_direction = horizontal_direction;
}

void PositionComponent::set_direction(VerticalDirection vertical_direction)
{
	_vertical_direction = vertical_direction;
}

void PositionComponent::set_direction(HorizontalDirection horizontal_direction, VerticalDirection vertical_direction)
{
	_horizontal_direction = horizontal_direction;
	_vertical_direction = vertical_direction;
}

PositionComponent::Direction PositionComponent::direction() const noexcept
{
	return {_horizontal_direction, _vertical_direction};
}

bool PositionComponent::operator==(const PositionComponent& other) const noexcept
{
	return _x == other._x && _y == other._y;
}

bool PositionComponent::operator!=(const PositionComponent& other) const noexcept
{
	return !(*this == other);
}

Component* PositionComponent::copy() const
{
	return new PositionComponent(_x, _y, _horizontal_direction, _vertical_direction);
}
