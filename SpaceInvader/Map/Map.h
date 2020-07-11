#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include <random>
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../ECS/Components/Base/Timer/Timer.h"

struct Rect {
	int x;
	int y;
	int width;
	int height;
};

class Map {
private:
	class Star : public Entity {
	public:
		Star(size_t x, size_t y);
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
	AutoResetTimer<> _stars_update_timer;
	inline static const size_t _stars_update_delay = 100;
public:
	Map(size_t frame_x, size_t frame_y, size_t width, size_t height);

	void update();
	void show_frame();
	Rect frame_position();
	Rect position();
	void show() const;
};

#endif