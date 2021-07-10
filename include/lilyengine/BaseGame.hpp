/*	BaseGame.hpp	-	Heather Crawford	-	07-09-2021
Abstract base class Game, sets up SDL systems & objects, 
*/
#pragma once
#ifndef _SDL2LE_BASEGAME_HPP_
#define _SDL2LE_BASEGAME_HPP_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class BaseGame
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
	int frame;

public:
	BaseGame(const char* title = "ExampleGame", int width = 640, int height = 480, bool run_instantly = false);
	virtual ~BaseGame() = 0;

	virtual void run();
};

#endif /* _SDL2LE_BASEGAME_HPP_ */