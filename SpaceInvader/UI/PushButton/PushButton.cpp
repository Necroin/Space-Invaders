#include "PushButton.h"
#include "../../WinAPI/WinAPI.h"

PushButton::PushButton(const char* text, UIObject* parent) :
	UIObject(parent, Base::Rectangle{ 0, 0, static_cast<int>(std::string_view(text).size()) + 2 , 3 }),
	_text(text)
{}

PushButton::PushButton(const std::string& text, UIObject* parent) :
	UIObject(parent, Base::Rectangle{ 0, 0, static_cast<int>(text.size()) + 2, 3 }),
	_text(text)
{}

PushButton::PushButton(int x, int y, const char* text) :
	UIObject(nullptr, Base::Rectangle{ x, y, static_cast<int>(std::string_view(text).size()) + 2 , 3 }),
	_text(text)
{}

PushButton::PushButton(int x, int y, const std::string& text) :
	UIObject(nullptr, Base::Rectangle{ x, y, static_cast<int>(text.size()) + 2, 3 }),
	_text(text)
{}

void PushButton::show() const
{
	WinAPI::put_symbol(218, _position.x, _position.y);
	WinAPI::put_symbol(191, _position.x + _position.width - 1, _position.y);
	WinAPI::put_symbol(192, _position.x, _position.y + _position.height - 1);
	WinAPI::put_symbol(217, _position.x + _position.width - 1, _position.y + _position.height - 1);

	WinAPI::put_symbol(196, _position.x + 1, _position.y, _text.size());
	WinAPI::put_symbol(196, _position.x + 1, _position.y + _position.height - 1, _text.size());

	for (size_t i = 1; i < _position.height - 1; ++i) {
		WinAPI::put_symbol(179, _position.x, _position.y + i);
		WinAPI::put_symbol(179, _position.x + _text.size() + 1, _position.y + i);
	}
	WinAPI::put_string(_text.c_str(), _text.size(), _position.x + 1, _position.y + 1);
}

void PushButton::hide() const
{
	for (size_t i = 0; i < _position.height; i++) {
		WinAPI::put_symbol(' ', _position.x, _position.y + i, _position.width);
	}
}

void PushButton::event()
{
	static auto mouse_pressed = []() -> bool
	{
		static bool pressed = false;
		static bool was_pressed = false;
		pressed = (GetKeyState(VK_LBUTTON) & 0x8000);
		if (pressed && !was_pressed) {
			was_pressed = true;
			return true;
		}
		was_pressed = pressed;
		return false;
	};
	if (mouse_pressed()) {
		auto mouse_coords = WinAPI::GetCursorWindowPosition();
		if (mouse_coords.X >= _position.x && mouse_coords.X < _position.x + _position.width &&
			mouse_coords.Y >= _position.y && mouse_coords.Y < _position.y + _position.height)
		{
			_pressed();
		}
	}
}

void PushButton::set_text(const std::string& text)
{
	_text = text;
}

IEvent<>& PushButton::pressed()
{
	return _pressed;
}
