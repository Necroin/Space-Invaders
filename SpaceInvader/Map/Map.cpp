#include "Map.h"
#include "../WinAPI/WinAPI.h"

void Map::create(size_t frame_x, size_t frame_y, size_t width, size_t height)
{
	_frame_x = frame_x;
	_frame_y = frame_y;
	_width = width;
	_height = height;
	_frame_width = width + 2;
	_frame_height = height + 2;

	_stars.clear();
	std::uniform_int_distribution<size_t> stars_distribution(1, _frame_y + _height);
	for (size_t i = 1; i <= _width; i = i + 3) {
		_stars.emplace_back(_frame_x + i, stars_distribution(_stars_random_device));
	}
}

void Map::update()
{
	if (!_stars_update_timer.tick()) {
		std::uniform_int_distribution<size_t> stars_distribution(1, _frame_y + _height);
		for (auto&& star : _stars) {
			decltype(auto) star_visible_component = star.get_component<VisibleComponent>();
			decltype(auto) star_position_component = star.get_component<PositionComponent>();
			star_visible_component.hide();
			star_position_component.move_forward();
			if (star_position_component.x() == _frame_x) {
				star_position_component.move_to(_frame_x + _width, stars_distribution(_stars_random_device));
			}
			star_visible_component.show();
		}
	}
}

Base::Rectangle Map::position()
{
	return { static_cast<int>(_frame_x + 1), static_cast<int>(_frame_y + 1), static_cast<int>(_width), static_cast<int>(_height) };
}

Base::Rectangle Map::frame_position()
{
	return { static_cast<int>(_frame_x), static_cast<int>(_frame_y), static_cast<int>(_frame_width), static_cast<int>(_frame_height) };
}

size_t Map::x()
{
	return _frame_x + 1;
}

size_t Map::y()
{
	return _frame_y + 1;
}

size_t Map::width()
{
	return _width;
}

size_t Map::height()
{
	return _height;
}

size_t Map::frame_x()
{
	return _frame_x;
}

size_t Map::frame_y()
{
	return _frame_y;
}

size_t Map::frame_width()
{
	return _frame_width;
}

size_t Map::frame_height()
{
	return _frame_height;
}

void Map::show()
{
	for (auto&& star : _stars) {
		star.get_component<VisibleComponent>().show();
	}
}

void Map::show_frame()
{
	WinAPI::put_symbol(218, _frame_x, _frame_y);
	WinAPI::put_symbol(191, _frame_x + _frame_width - 1, _frame_y);
	WinAPI::put_symbol(192, _frame_x, _frame_y + _frame_height - 1);
	WinAPI::put_symbol(217, _frame_x + _frame_width - 1, _frame_y + _frame_height - 1);

	WinAPI::put_symbol(196, _frame_x + 1, _frame_y, _frame_width - 2);
	WinAPI::put_symbol(196, _frame_x + 1, _frame_y + _frame_height - 1, _frame_width - 2);

	for (size_t i = _frame_y + 1; i < _frame_height - 1; ++i) {
		WinAPI::put_symbol(179, _frame_x, _frame_y + i);
		WinAPI::put_symbol(' ', _frame_x + 1, _frame_y + i, _frame_width - 2);
		WinAPI::put_symbol(179, _frame_x + _frame_width - 1, _frame_y + i);
	}
}

void Map::hide()
{
}

bool Map::in_map(int x, int y)
{
	return x > _frame_x && y > _frame_y && x <= _frame_x + _width && y <= _frame_y + _height;
}

Map::Star::Star(size_t x, size_t y)
{
	this->add_component<PositionComponent>(x, y, PositionComponent::HorizontalDirection::left);
	this->add_component<VisibleComponent>('*');
}
