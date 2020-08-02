#pragma once
#ifndef _PUSHBUTTON_H_
#define _PUSHBUTTON_H_
#include "../UIObject/UIObject.h"
#include <string>
#include <string_view>

class PushButton :
	public UIObject
{
private:
	std::string _text;
public:
	PushButton(const char* text);
	PushButton(const std::string& text);
	PushButton(int x, int y, const char* text);
	PushButton(int x, int y, const std::string& text);
	virtual void show() const override;
	virtual void hide() const override;
	virtual void event() override;
	void set_text(const std::string& text);
};
#endif