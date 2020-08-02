#include "Layout.h"

Layout::Layout(UIObject* parent, int x, int y, int step) :
	UIObject(parent, Base::Rectangle{ x, y, 0 ,0 }),
	_step(step)
{}

Layout::~Layout() {}

void Layout::show() const
{
	for (auto&& object : _objects) {
		object->show();
	}
}

void Layout::hide() const
{
	for (auto&& object : _objects) {
		object->hide();
	}
}

void Layout::event()
{
	for (auto&& object : _objects) {
		object->event();
	}
}

std::unique_ptr<UIObject>& Layout::operator[](std::size_t index)
{
	return _objects[index];
}
