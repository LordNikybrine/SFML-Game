#include "Game.h"

int main() {

	//init game engine
	Game game;

	//Game loop
	while (game.running()) {

		//////Update//////
		game.update();
		//////Render//////
		game.render();
	}

	return 0;
}