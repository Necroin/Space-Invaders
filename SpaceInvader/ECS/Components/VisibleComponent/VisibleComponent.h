#pragma once
#ifndef _VISIBLECOMPONENT_H_
#define _VISIBLECOMPONENT_H_
#include "../../ECS.h"

/**
cunstructor : VisibleComponent(char symbol, int color = Color::White)
methoods :
void show() const
void hide() const
void set_color(int color)
*/
class VisibleComponent : public Component
{
public:
	enum Color : int {
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
protected:
	char _symbol;
	int _color;
	int _default_color;
public:
	VisibleComponent(char symbol, int color = Color::White);
	void show() const;
	void hide() const;
	void set_color(int color);
	virtual Component* copy() override;
};
#endif