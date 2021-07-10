/*
*/
#include "BaseGame.hpp"
#include <iostream>

BaseGame::BaseGame(const char* title, int width, int height, bool run_instantly)
{
	isRunning = false;
	frame = 0;

	bool sdl_initialized = SDL_Init(SDL_INIT_EVERYTHING);
	if(sdl_initialized != 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	bool ttf_initialized = TTF_Init();
	if(ttf_initialized == -1)
	{
		std::cout << "SDL_TTF could not initialize! SDL Error: " << TTF_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if(window == NULL)
	{
		std::cout << "SDL could not make a window! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if(window == NULL)
	{
		std::cout << "SDL could not make a renderer! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	isRunning = true;
	std::cout << "Game Initialized!" << std::endl;

	if(run_instantly)
	{
		run();
	}
}

void BaseGame::run()
{
	std::cout << "Running game..." << std::endl;
	SDL_Event event;

	while (isRunning)
	{
		frame++;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, frame, frame, frame, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}
}

BaseGame::~BaseGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}