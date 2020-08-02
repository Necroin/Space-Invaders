#pragma once
#ifndef _POSITIONCOMPONENT_H_
#define _POSITIONCOMPONENT_H_
#include "../../ECS.h"

class PositionComponent : 
	public Component
{
public:
	struct Coordinates {
		int x;
		int y;
	};
	enum class HorizontalDirection {
		null,
		left,
		right
	};
	enum class VerticalDirection {
		null,
		up,
		down
	};
	struct Direction {
		PositionComponent::HorizontalDirection horizontal_direction;
		PositionComponent::VerticalDirection vertical_direction;
	};
private:
	int _x;
	int _y;
	HorizontalDirection _horizontal_direction;
	VerticalDirection _vertical_direction;
public:
	PositionComponent(int x, int y);
	PositionComponent(
		int x,
		int y,
		HorizontalDirection horizontal_direction,
		VerticalDirection vertical_direction = VerticalDirection::null
	);
	PositionComponent(
		int x,
		int y,
		VerticalDirection vertical_direction,
		HorizontalDirection horizontal_direction = HorizontalDirection::null
	);
public:
	int x() const noexcept;
	int y() const noexcept;
	int forward_x() const noexcept;
	int forward_y() const noexcept;
	Coordinates coordinates();
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void move_to(int x, int y);
	void move_forward();
	void set_direction(HorizontalDirection horizontal_direction);
	void set_direction(VerticalDirection vertical_direction);
	void set_direction(HorizontalDirection horizontal_direction, VerticalDirection vertical_direction);
	Direction direction() const noexcept;
	bool operator==(const PositionComponent& other) const noexcept;
	bool operator!=(const PositionComponent& other) const noexcept;
	virtual Component* copy() const override;
};
#endif