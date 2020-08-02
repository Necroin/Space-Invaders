#include "VisibleComponent.h"
#include "../../WinAPI/WinAPI.h"
#include "../PositionComponent/PositionComponent.h"
#include "../../../Map/Map.h"

VisibleComponent::VisibleComponent(char symbol, int color) :
	_symbol(symbol),
	_color(color),
	_default_color(Color::White)
{}

void VisibleComponent::show() const
{
	if (_entity->has_component<PositionComponent>()) {
		auto [x, y] = _entity->get_component<PositionComponent>().coordinates();
		if (Map::in_map(x, y)) {
			if (_color == _default_color) {
				WinAPI::put_symbol(_symbol, x, y);
			}
			else {
				WinAPI::put_color_symbol(_symbol, x, y, _color);
			}
		}
	}
}

void VisibleComponent::hide() const
{
	if (_entity->has_component<PositionComponent>()) {
		auto [x, y] = _entity->get_component<PositionComponent>().coordinates();
		if (Map::in_map(x, y)) {
			if (_color == _default_color) {
				WinAPI::put_symbol(' ', x, y);
			}
			else {
				WinAPI::put_color_symbol(' ', x, y, _default_color);
			}
		}
	}
}

int VisibleComponent::color() const noexcept
{
	return _color;
}

void VisibleComponent::set_color(int color)
{
	_color = color;
}

Component* VisibleComponent::copy() const
{
	return new VisibleComponent(_symbol,_color);
}
