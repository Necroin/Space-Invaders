#include "MoveComponent.h"

MoveComponent::MoveComponent(int x, int y) :
	Coordinates(x, y)
{}

void MoveComponent::move_left()
{
	--_x;
}

void MoveComponent::move_right()
{
	++_x;
}

void MoveComponent::move_up()
{
	--_y;
}

void MoveComponent::move_down()
{
	++_y;
}

void MoveComponent::move_to(int x, int y)
{
	_x = x;
	_y = y;
}
