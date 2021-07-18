/**
 * @file BaseGame.cpp
 * @author lilitharcana (lilithalicecrawford@gmail.com)
 * @brief Implementation for BaseGame class from BaseGame.hpp.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "SDLError.hpp"
#include "BaseGame.hpp"
#include <iostream>

namespace LilyEngine {

	/**
	 * @brief Construct a BaseGame object, with a given title, window size, and autorun flag.
	 * Initializes SDL and its subsystems, creates SDL window and renderer, and sets up LilyEngine systems.
	 * If autorun is true, the game will automatically start and run inside the constructor.
	 * If you need an exit code for the game, call run() seperately.
	 * 
	 * @param title The title of the window.
	 * @param width width of the window.
	 * @param height height of the window.
	 * @param autorun Whether or not to automatically run the game.
	 */
	BaseGame::BaseGame(const char* title, int width, int height, bool autorun)
	{	
		bool systems_initialized = init_sdl_systems(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);
		if (!systems_initialized)
		{
			error("SDL systems could not be initialized!", SDL);
			return;
		}
		printf("SDL systems initialized!");

		bool resources_initialized = load_engine_resources();
		if (!resources_initialized)
		{
			error("Resources could not be initialized!", SDL);
			return;
		}
		printf("Resources initialized!");

		clock.running = true;	// Start the game clock, needed to run the game.
		std::cout << "Engine Initialized!" << std::endl;

		if(autorun) run();
	}

	/**
	 * @brief The main game loop. Updates clock, checks for events, updates game logic, and renders the screen.
	 * Exits if isRunning is false.
	 */
	void BaseGame::run()
	{
		bool game_initialized = init();
		if (!game_initialized)
		{
			error("Game init() failed!", SDL);
			return;
		}
		printf("Game initialized!");

		std::cout << "Running game..." << std::endl;
		SDL_Event event;

		while (clock.running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					clock.running = false;
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						clock.running = false;
					}
				}
			}

			SDL_SetRenderDrawColor(renderer, clock.ticks, clock.ticks, clock.ticks, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);

			SDL_RenderPresent(renderer);
			clock.tick();
		}
	}

	/**
	 * @brief Frees your resources with cleanup(), destroys LilyEngine and SDL systems.
	 */
	BaseGame::~BaseGame()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		TTF_Quit();
		SDL_Quit();
	}
	


	/* 
	 * ---------------------------------------
	 * Private Methods - Engine implementation
	 * ---------------------------------------
	 */ 



	/**
	 * @brief Private internal method to initialize SDL systems.
	 * 
	 * @param title the initial title of the window.
	 * @param xpos window x position (defaults to center)
	 * @param ypos window y position (defaults to center)
	 * @param width window width (defaults to 640)
	 * @param height window height (defaults to 480)
	 * @param fullscreen window fullscreen flag (defaults to false)
	 * @param sdl_init_flags flags to pass to SDL_Init()
	 * @return true if SDL and subsystems was initialized successfully, false otherwise.
	 */
	bool BaseGame::init_sdl_systems(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Uint32 sdl_init_flags)
	{
		
		bool sdl_initialized = SDL_Init(sdl_init_flags);
		if(sdl_initialized != 0)
		{
			std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		bool ttf_initialized = TTF_Init();
		if(ttf_initialized == -1)
		{
			std::cout << "SDL_TTF could not initialize! SDL Error: " << TTF_GetError() << std::endl;
			return false;
		}

		window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
		if(window == NULL)
		{
			std::cout << "SDL could not make a window! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
		if(window == NULL)
		{
			std::cout << "SDL could not make a renderer! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}
	
	/**
	 * @brief Loads internal engine resources, like a default font, etc.
	 * 
	 * @return true if resources were loaded successfully, false otherwise.
	 */
	bool BaseGame::load_engine_resources() 
	{
		// Load a font
		std::string font_path = "resources/712_serif.ttf";
		font = TTF_OpenFont(font_path.c_str(), 24);
		if (font == NULL)
		{
			error("Unable to load font \"" + font_path + "\".", TTF);
			return false;
		}

		// Load a text box
		textbox = new LTextBox(font, "Here is some default text!");
		textbox->setRect(SDL_Rect{ 50, 50, 590, 430 });
		return true;
	}
	
	/**
	 * @brief Events that the game engine needs to handle.
	 * 
	 * @return true if the event was handled, false otherwise and needs to be handled by the game implementation.
	 */
	bool BaseGame::engine_handle_events() 
	{
		return false;
	}
	
	/**
	 * @brief Updates engine logic.
	 */
	void BaseGame::engine_update() 
	{
		
	}
	
	void BaseGame::engine_render() 
	{
		textbox->render(renderer);
		SDL_RenderPresent(renderer);
	}
	
	/**
	 * @brief Frees engine resources & systems.
	 */
	void BaseGame::engine_clean() 
	{
		// free resources
		delete textbox;
		TTF_CloseFont(font);
		// free SDL subsystems
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

}