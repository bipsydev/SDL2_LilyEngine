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

// My engine headers
#include "Clock.hpp"

// SDL headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Standard C++ headers
#include <string>


namespace LilyEngine {

	class BaseGame
	{
	public:
		// Engine create
		BaseGame(const char* title, int width = 640, int height = 480, bool run_instantly = false);
		// Engine destroy (free engine & subclass resources)
		virtual ~BaseGame() = 0;

		// Runs the engine game loop.
		virtual void run();

	protected:
		// Initialize your game objects, global variables, set inputs, load resources, configure systems, etc.
		virtual void init() = 0;

		// The main game loop, run() will call these functions every frame:
		virtual bool event(SDL_Event& event) = 0;	// React to an event (window close, key press, etc), return true if the event was handled.
		virtual void update() = 0;					// Update game variables based on events/inputs/etc.
		virtual void render() = 0;					// Render the graphics for the current frame.

		// Save the game if needed, unload resources, quit systems.
		virtual void cleanup() = 0;

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		LilyEngine::Clock clock{};

		// init SDL and subsystems.
		bool init_sdl_systems(const char* title,									// window title
			int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED,	// window position
			int width = 640, int height = 480,										// window size
			bool fullscreen = false,												// fullscreen bool
			Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);							// SDL_Init() flags
		
		// load necessary inital resources.
		bool load_engine_resources();

		// behind the scenes engine updating, every frame
		bool engine_handle_events();
		void engine_update();
		void engine_render();

		// clean up all engine systems & resources
		void engine_clean();


	};

}

#endif /* _SDL2_LILYENGINE_BASEGAME_HPP_ */