#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include <random>
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../Base/Timer/Timer.h"
#include "../Base/Rectangle/Rectangle.h"

class Map {
private:
	inline static size_t _frame_x;
	inline static size_t _frame_y;
	inline static size_t _frame_width;
	inline static size_t _frame_height;
	inline static size_t _width;
	inline static size_t _height;
private:
	class Star : 
		public Entity
	{
	public:
		Star(size_t x, size_t y);
	};
private:
	inline static std::random_device _stars_random_device;
	inline static std::vector<Star> _stars;
	inline static const size_t _stars_update_delay = 100;
	inline static AutoResetTimer<> _stars_update_timer = AutoResetTimer<>(_stars_update_delay);
public:
	static void create(size_t frame_x, size_t frame_y, size_t width, size_t height);
	static void update();
	static Base::Rectangle position();
	static Base::Rectangle frame_position();
	static size_t x();
	static size_t y();
	static size_t width();
	static size_t height();
	static size_t frame_x();
	static size_t frame_y();
	static size_t frame_width();
	static size_t frame_height();
	static void show();
	static void show_frame();
	static void hide();
	static bool in_map(int x, int y);
};

#endif