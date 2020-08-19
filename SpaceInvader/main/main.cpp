#include "../Game/Game.h"
#include <Windows.h>

int main(int argc, char* argv[]) {
	Game game;
	while (game.is_active()) {
		game.run();
	}
	return 0;
}