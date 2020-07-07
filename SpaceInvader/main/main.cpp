#include "../Game/Game.h"
#include <Windows.h>
int main(int argc, char* argv[]) {
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
	Game game;
	while (game.is_active())
	{
		game.action();
		game.update();
		game.render();
	}
	return 0;
}