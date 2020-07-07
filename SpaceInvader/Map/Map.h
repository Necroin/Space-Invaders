#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include <random>
#include "../Components/MoveComponent/MoveComponent.h"
#include "../Components/VisibleComponent/VisibleComponent.h"
#include "../Components/Base/Timer/Timer.h"

struct Rect {
	int x;
	int y;
	int width;
	int height;
};

class Map {
private:
	class Star : public MoveComponent, public VisibleComponent {
	public:
		Star(Map& map, size_t x, size_t y);
		bool move();
	};
private:
	size_t _frame_x;
	size_t _frame_y;
	size_t _frame_width;
	size_t _frame_height;
	size_t _width;
	size_t _height;
	std::random_device _stars_random_device;
	std::vector<Star> _stars;
	AutoResetTimer _stars_update_timer;
	inline static const size_t _stars_update_delay = 100;
public:
	Map(size_t frame_x, size_t frame_y, size_t width, size_t height);

	void update();
	void show();
	void show_frame();
	Rect frame_position();
	Rect position();
};

#endif