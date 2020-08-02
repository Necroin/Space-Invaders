#include "HorizontalLayout.h"

void HorizontalLayout::update_position()
{
	bool first_object_flag = true;
	decltype(auto) object_position = &HorizontalLayout::_position;
	_position.width = 0;
	for (auto&& object : _objects) {
		decltype(auto) object_update_positiion = &HorizontalLayout::UIObject::update_position;
		if (first_object_flag) {
			(*object.*object_position).x = _position.x;
			_position.width += (*object.*object_position).width;
			first_object_flag = false;
		}
		else {
			(*object.*object_position).x = _position.x + _position.width + _step;
			_position.width += ((*object.*object_position).width + _step);
		}
		if (object->height() > _position.height) {
			_position.height = object->height();
			if (_parent) {
				decltype(auto) parent_update_height = &HorizontalLayout::UIObject::update_height;
				(_parent->*parent_update_height)(_position.height);
			}
		}
		if (_model == Model::up) {
			(*object.*object_position).y = _position.y;
		}
		if (_model == Model::centre) {
			(*object.*object_position).y = (_position.y * 2 + _position.height - 1) / 2 - object->height() / 2;
		}
		if (_model == Model::down) {
			(*object.*object_position).y = (_position.y + _position.height - 1) - object->height();
		}
		((*object).*object_update_positiion)();
	}
}

HorizontalLayout::HorizontalLayout(int x, int y, int step, Model model) :
	Layout(nullptr, x, y, step),
	_model(model)
{}

HorizontalLayout::HorizontalLayout(UIObject * parent, int step, Model model) :
	Layout(parent, 0, 0, step),
	_model(model)
{}

void HorizontalLayout::set_model(Model model)
{
	_model = model;
	decltype(auto) root_update_position = &HorizontalLayout::UIObject::update_position;
	(root()->*root_update_position)();
}
