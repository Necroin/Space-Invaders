#pragma once
#ifndef _MOVECOMPONENT_H_
#define _MOVECOMPONENT_H_
#include "../Base/Coordinates/Coordinates.h"

class MoveComponent : virtual public Coordinates
{
public:
	MoveComponent(int x, int y);
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void move_to(int x, int y);
};
#endif