#include "VerticalLayout.h"

void VerticalLayout::update_position()
{
	bool first_object_flag = true;
	decltype(auto) object_position = &VerticalLayout::_position;
	_position.height = 0;
	for (auto&& object : _objects) {
		decltype(auto) object_update_positiion = &VerticalLayout::UIObject::update_position;
		if (first_object_flag) {
			(*object.*object_position).y = _position.y;
			_position.height += (*object.*object_position).height;
			first_object_flag = false;
		}
		else {
			(*object.*object_position).y = _position.y + _position.height + _step;
			_position.height += ((*object.*object_position).height + _step);
		}
		if (object->width() > _position.width) {
			_position.width = object->width();
			if (_parent) {
				decltype(auto) parent_update_width = &VerticalLayout::UIObject::update_width;
				(_parent->*parent_update_width)(_position.width);
			}
		}
		if (_model == Model::left) {
			(*object.*object_position).x = _position.x;
		}
		if (_model == Model::centre) {
			(*object.*object_position).x = (_position.x * 2 + _position.width - 1) / 2 - object->width() / 2;
		}
		if (_model == Model::right) {
			(*object.*object_position).x = (_position.x + _position.width - 1) - object->width();
		}
		((*object).*object_update_positiion)();
	}
}

VerticalLayout::VerticalLayout(int x, int y, int step, Model model) :
	Layout(nullptr, x, y, step),
	_model(model)
{}

VerticalLayout::VerticalLayout(UIObject * parent, int step, Model model) :
	Layout(parent, 0, 0, step),
	_model(model)
{}

void VerticalLayout::set_model(Model model)
{
	_model = model;
	decltype(auto) root_update_position = &VerticalLayout::UIObject::update_position;
	(root()->*root_update_position)();
}
