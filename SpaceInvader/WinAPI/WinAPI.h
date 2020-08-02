#pragma once
#ifndef _WINAPI_H_
#define _WINAPI_H_
#include <Windows.h>

namespace WinAPI {
	COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

	void gotoxy(HANDLE hConsole, int x, int y);
	void gotoxy(int x, int y);

	COORD GetCursorWindowPosition();

	void put_symbol(char symbol, size_t x, size_t y, size_t count = 1);
	void put_color_symbol(char symbol, size_t x, size_t y, int color, size_t count = 1);
	void put_string(const char* string, size_t length, size_t x, size_t y);
}
#endif