#include "VisibleComponent.h"
#include "../../WinAPI/WinAPI.h"

VisibleComponent::VisibleComponent(int x, int y, char symbol, int color) :
	Coordinates(x,y),
	_symbol(symbol),
	_color(color),
	_default_color(Color::White)
{}

void VisibleComponent::show()
{
	if (_color == _default_color) {
		WinAPI::put_symbol(_symbol, _x, _y);
	}
	else {
		WinAPI::put_symbol(_symbol, _x, _y, _color);
	}
}

void VisibleComponent::hide()
{
	if (_color == _default_color) {
		WinAPI::put_symbol(' ', _x, _y);
	}
	else {
		WinAPI::put_symbol(' ', _x, _y, _default_color);
	}
}

void VisibleComponent::set_color(int color)
{
	_color = color;
}
