/**
 * @file BaseGame.hpp
 * @author lilitharcana (lilithalicecrawford@gmail.com)
 * @brief Main abstract class to inherit for all games made with SDL_LilyEngine.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#ifndef _SDL2_LILYENGINE_BASEGAME_HPP_
#define _SDL2_LILYENGINE_BASEGAME_HPP_

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

#endif /* _SDL2_LILYENGINE_BASEGAME_HPP_ */