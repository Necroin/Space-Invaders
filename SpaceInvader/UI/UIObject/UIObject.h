#pragma once
#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_
#include "../../Base/Rectangle/Rectangle.h"

class UIObject {
protected:
	Base::Rectangle _position;
	UIObject* _parent;
protected:
	virtual void update_position();
	void update_width(int width);
	void update_height(int height);
	UIObject* root();
public:
	UIObject(UIObject* parent, const Base::Rectangle& position);
	virtual ~UIObject();
public:
	virtual void show() const = 0;
	virtual void hide() const = 0;
	virtual void event();
	int x() const noexcept;
	int y() const noexcept;
	int width() const noexcept;
	int height() const noexcept;
	const Base::Rectangle& position() const noexcept;
};
#endif