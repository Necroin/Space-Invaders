#pragma once
#ifndef _COORDINATES_H_
#define _COORDINATES_H_
#include <utility>

class Coordinates {
protected:
	int _x;
	int _y;
public:
	Coordinates(int x, int y);
	std::pair<int, int> coordinates();
	bool operator == (const Coordinates& other) { return this->_x == other._x && this->_y == other._y; }
	bool operator != (const Coordinates& other) { return !(*this == other); }
};
#endif