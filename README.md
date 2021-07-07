# SDL2_GameEngine
Learning SDL2 and C++ by making a game engine!

```C++

int main(int argc, char* argv[])
{
	game = new Game("Instance of lilitharcana's Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false, DEBUG);
	while (game->isRunning())
	{
		game->handleEvents();			// handle any events
		game->update();					// update the game
		game->render();					// render the frame (waits until graphics card is ready, then displays)

		debug (							// some debug info
			printGameGetFrameNumber();	// game->getFrameNumber() isn't working ??
			game->printFrameNumber();	// this one works tho (?)
		)

		game->tick();					// update game time
	}

	game->clean();
	delete game;
	return 0;
}

```
