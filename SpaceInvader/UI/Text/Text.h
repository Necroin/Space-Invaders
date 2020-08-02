#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_
#include "../UIObject/UIObject.h"
#include <string>
#include <string_view>

class Text : 
	public UIObject
{
private:
	std::string _text;
public:
	Text(const char* text, UIObject* parent = nullptr);
	Text(const std::string& text, UIObject* parent = nullptr);
	Text(int x, int y, const char* text);
	Text(int x, int y, const std::string& text);
public:
	const std::string text();
	void set_text(const std::string& text);
	void set_text(const char* text);
	virtual void show() const override;
	virtual void hide() const override;
};
#endif
