#pragma once
#ifndef _VERTICALLAYOUT_H_
#define _VERTICALLAYOUT_H_
#include "../Layout.h"

class VerticalLayout :
	public Layout
{
public:
	enum class Model {
		left,
		centre,
		right
	};
private:
	virtual void update_position() override;
	Model _model;
public:
	VerticalLayout(int x, int y, int step = 1, Model model = Model::centre);
	VerticalLayout(UIObject* parent, int step = 1, Model mode = Model::centre);
	template<class _UIObject, class... Args>
	_UIObject& add_object(Args&&... args) {
		_objects.emplace_back(std::make_unique<_UIObject>(std::forward<Args>(args)...));
		decltype(auto) object = *_objects.back();
		decltype(auto) object_position = &VerticalLayout::_position;
		if (_objects.size() == 1) {
			(object.*object_position).y = _position.y;
			_position.height += (object.*object_position).height;
		}
		else {
			(object.*object_position).y = _position.y + _position.height + _step;
			_position.height += ((object.*object_position).height + _step);
		}
		if (object.width() > _position.width) {
			_position.width = object.width();
			if (_parent) {
				decltype(auto) parent_update_width = &VerticalLayout::UIObject::update_width;
				(_parent->*parent_update_width)(_position.width);
			}
		}
		if (_parent) {
			decltype(auto) parent_update_height = &VerticalLayout::UIObject::update_height;
			(_parent->*parent_update_height)(_position.height);
		}
		decltype(auto) root_update_position = &VerticalLayout::UIObject::update_position;
		(root()->*root_update_position)();
		if (_model == Model::left) {
			(object.*object_position).x = _position.x;
		}
		if (_model == Model::centre) {
			(object.*object_position).x = (_position.x * 2 + _position.width - 1) / 2 - object.width() / 2;
		}
		if (_model == Model::right) {
			(object.*object_position).x = (_position.x + _position.width - 1) - object.width();
		}
		return static_cast<_UIObject&>(object);
	}

	void set_model(Model model);
};
#endif