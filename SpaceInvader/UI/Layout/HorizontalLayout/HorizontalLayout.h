#pragma once
#ifndef _HORIZONTALLAYOUT_H_
#define _HORIZONTALLAYOUT_H_
#include "../Layout.h"

class HorizontalLayout :
	public Layout
{
public:
	enum class Model {
		up,
		centre,
		down
	};
private:
	virtual void update_position() override;
	Model _model;
public:
	HorizontalLayout(int x, int y, int step = 1, Model objects_model = Model::centre);
	HorizontalLayout(UIObject* parent, int step = 1, Model objects_model = Model::centre);
	template<class _UIObject, class... Args>
	_UIObject& add_object(Args&&... args) {
		_objects.emplace_back(std::make_unique<_UIObject>(std::forward<Args>(args)...));
		decltype(auto) object = *_objects.back();
		decltype(auto) object_position = &HorizontalLayout::_position;
		if (_objects.size() == 1) {
			(object.*object_position).x = _position.x;
			_position.width += (object.*object_position).width;
		}
		else {
			(object.*object_position).x = _position.x + _position.width + _step;
			_position.width += ((object.*object_position).width + _step);
		}
		if (object.height() > _position.height) {
			_position.height = object.height();
			if (_parent) {
				decltype(auto) parent_update_height = &HorizontalLayout::UIObject::update_height;
				(_parent->*parent_update_height)(_position.height);
			}
		}
		if (_parent) {
			decltype(auto) parent_update_width = &HorizontalLayout::UIObject::update_width;
			(_parent->*parent_update_width)(_position.width);
		}
		decltype(auto) root_update_position = &HorizontalLayout::UIObject::update_position;
		(root()->*root_update_position)();
		if (_model == Model::up) {
			(object.*object_position).y = _position.y;
		}
		if (_model == Model::centre) {
			(object.*object_position).y = (_position.y * 2 + _position.height - 1) / 2 - object.height() / 2;
		}
		if (_model == Model::down) {
			(object.*object_position).y = (_position.y + _position.height - 1) - object.height();
		}
		return static_cast<_UIObject&>(object);
	}

	void set_model(Model model);
};
#endif