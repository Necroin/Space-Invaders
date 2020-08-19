#include "Text.h"
#include "../../WinAPI/WinAPI.h"

Text::Text(const char* text, UIObject* parent) :
	UIObject(parent, Base::Rectangle{ 0, 0, static_cast<int>(std::string_view(text).size()), 1 }),
	_text(text)
{}

Text::Text(const std::string& text, UIObject* parent) :
	UIObject(parent, Base::Rectangle{ 0, 0, static_cast<int>(text.size()), 1 }),
	_text(text)
{}

Text::Text(int x, int y, const char* text) :
	UIObject(nullptr, Base::Rectangle{ x, y, static_cast<int>(std::string_view(text).size()), 1 }),
	_text(text)
{}

Text::Text(int x, int y, const std::string & text) :
	UIObject(nullptr, Base::Rectangle{ x, y, static_cast<int>(text.size()), 1 }),
	_text(text)
{}

const std::string Text::text()
{
	return _text;
}

void Text::set_text(const std::string& text)
{
	std::size_t prev_width = _position.width;
	_text = text;
	_position.width = _text.size();
	if (!_hiden) WinAPI::put_symbol(' ', _position.x, _position.y, prev_width);
	if (prev_width != _position.width) {
		decltype(auto) root_update_position = &Text::UIObject::update_position;
		(root()->*root_update_position)();
		if (!_hiden) {
			root()->hide();
			root()->show();
		}
	}
	else {
		if (!_hiden) WinAPI::put_string(_text.c_str(), _position.width, _position.x, _position.y);
	}
}

void Text::set_text(const char* text)
{
	std::size_t prev_width = _position.width;
	_text = text;
	_position.width = _text.size();
	if (!_hiden) WinAPI::put_symbol(' ', _position.x, _position.y, prev_width);
	if (prev_width != _position.width) {
		decltype(auto) root_update_position = &Text::UIObject::update_position;
		(root()->*root_update_position)();
		if (!_hiden) {
			root()->hide();
			root()->show();
		}
	}
	else {
		if (!_hiden) WinAPI::put_string(_text.c_str(), _position.width, _position.x, _position.y);
	}
}

void Text::show() const
{
	WinAPI::put_string(_text.c_str(), _position.width, _position.x, _position.y);
	_hiden = false;
}

void Text::hide() const
{
	WinAPI::put_symbol(' ', _position.x, _position.y, _position.width);
	_hiden = true;
}
