#pragma once
#ifndef _POSITIONCOMPONENT_H_
#define _POSITIONCOMPONENT_H_
#include "../../ECS.h"


/**
constructor : PositionComponent(int x, int y, int forward_direction)
methoods :
int x()
int y()
void move_left()
void move_right()
void move_up()
void move_down()
*/
class PositionComponent : public Component {
public:
	enum Direction {
		left,
		up,
		right,
		down
	};
private:
	int _x;
	int _y;
	int _forward_direction;
public:
	void move_left();
	void move_right();
	void move_up();
	void move_down();
private:
	inline static std::array<decltype(&move_left),4> _direction_move = {
		&move_left,
		&move_up,
		&move_right,
		&move_down
	};
public:
	PositionComponent(int x, int y, int forward_direction);
	
	int x();
	int forward_x();
	int y();
	int forward_y();
	std::pair<int, int> coordinates();
	void move_to(int x, int y);
	void move_forward();
	bool operator==(const PositionComponent& other);
	bool operator!=(const PositionComponent& other);
	virtual Component* copy() const override;
};
#endif