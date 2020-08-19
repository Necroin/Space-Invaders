#pragma once
#ifndef _PUSHBUTTON_H_
#define _PUSHBUTTON_H_
#include "../UIObject/UIObject.h"
#include "../../EventSystem/EventSystem.h"
#include <string>
#include <string_view>

class PushButton :
	public UIObject
{
private:
	std::string _text;
	Event<> _pressed;
public:
	PushButton(const char* text, UIObject* parent = nullptr);
	PushButton(const std::string& text, UIObject* parent = nullptr);
	PushButton(int x, int y, const char* text);
	PushButton(int x, int y, const std::string& text);
	virtual void show() const override;
	virtual void hide() const override;
	virtual void event() override;
	void set_text(const std::string& text);
	IEvent<>& pressed();
};
#endif