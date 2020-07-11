#pragma once
#ifndef _POSITIONCOMPONENT_H_
#define _POSITIONCOMPONENT_H_
#include "../../ECS.h"


/**
- PositionComponent(int x, int y)
*/
class PositionComponent : public Component {
private:
	int _x;
	int _y;
public:
	PositionComponent(int x, int y);
	int x();
	int y();
	std::pair<int, int> coordinates();
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void move_to(int x, int y);
	bool operator==(const PositionComponent& other);
	bool operator!=(const PositionComponent& other);
	virtual Component* copy() override;
};
#endif