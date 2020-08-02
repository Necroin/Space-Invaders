#pragma once
#ifndef _LAYOUT_H_
#define _LAYOUT_H_
#include "../UIObject/UIObject.h"
#include <vector>
#include <memory>

class Layout :
	public UIObject
{
protected:
	std::vector<std::unique_ptr<UIObject>> _objects;
	int _step;
public:
	Layout(UIObject* parent, int x, int y, int step);
	virtual ~Layout();
public:
	virtual void show() const override;
	virtual void hide() const override;
	virtual void event() override;
	std::unique_ptr<UIObject>& operator[](std::size_t index);
};
#endif