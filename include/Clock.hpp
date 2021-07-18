/* Clock.h	-	Heather Crawford	-	07-03-2021
*
* Helper clock class to keep track of SDL tick and game time and report a delta time between frames!
* Just call tick() every update.
*/
#pragma once
#ifndef _SDL2_LILYENGINE_CLOCK_HPP_
#define _SDL2_LILYENGINE_CLOCK_HPP_

#include <SDL.h>
#include <math.h>
#include <algorithm>

namespace LilyEngine {

	/**
	 * @brief Clock struct to keep track of game time, delta time, ticks, framerate, vsync, etc.
	 */
	struct Clock
	{
	public:
		bool running = false;		// this determines if the main loop should loop another frame.
		// set this to true when everything has initialized correctly, then false when we want the game to end next frame.

		Uint64 last_tick_time = 0;	// holds the last call to SDL_GetPerformanceCounter()
		float delta = 0;			// calculated seconds since last tick
		float delta_ms = 0;			// delta, but in milliseconds
		int ticks = 0;				// times tick has been called

		float seconds = 0;			// seconds since startup
		int minutes = 0;			// minutes since startup
		int hours = 0;				// hours since startup

		/**
		 * @brief This will update game time variables based on SDL_GetTicks(), then delay based on desired FPS.
		 * isVSyncOn should be set to true if SDL_RENDERER_PRESENTVSYNC was passed to the renderer.
		 * fps should be only set if vsync is false. -1 is unlimited.
		 * 
		 * @param isVSyncOn tell tick() if hardware vsync is on.
		 * @param fps The desired frame rate.
		 */
		void tick(bool isVSyncOn = true, float fps = -1)
		{
			Uint64 tick_time = get_time_from_SDL();	// update our tick time from SDL
			delta = calculate_delta(tick_time);		// get delta time from tick
			delta_ms = delta * 1000.0f;				// convert to milliseconds
			
			update_clocks();

			if (!isVSyncOn)	// if hardware vsync is off and we need to cap framerate...
			{
				cap_framerate(fps);
			}

			/*
			* Set up for next frame (tick)
			*/
			ticks++;						// increase ticks (essentially frame count)
			last_tick_time = tick_time;		// save tick_time into last_tick_time for the next tick() call
		}

	private:
		/**
		 * @brief Get the time from SDL using system-specific high-resolution timer.
		 * 
		 * @return Uint64 SDL_GetPerformanceCounter()
		 */
		Uint64 get_time_from_SDL()
		{
			return SDL_GetPerformanceCounter();
		}

		/**
		 * @brief Calculate the delta time from last tick using new (current) tick time,
		 * last tick time, and dividing by performance frequency to get delta seconds.
		 * 
		 * @param new_tick_time Should be from get_time_from_SDL()
		 * @return float Delta time in seconds.
		 */
		float calculate_delta(Uint64 new_tick_time)
		{
			if (last_tick_time != 0)
			{
				float _elapsed = new_tick_time - last_tick_time;				// get elapsed time since last tick()
				// SDL_GetPerformanceCounter() is system specific; we must divide by frequency per second to get our delta time.
				return _elapsed / (float)SDL_GetPerformanceFrequency();	// this is in seconds
			}
			else {
				return 0;
			}
		}

		/**
		 * @brief Update seconds, minutes, and hours after delta has been calculated.
		 */
		void update_clocks()
		{
			seconds += delta;						// add delta time to our seconds counter
			minutes = (int)floor(seconds / 60.0);	// get minutes since startup (int)
			hours = (int)floor(seconds / 3600.0);	// get hours since startup (int)

			//verbose_debug(println("Game Time: " << seconds << "s, " << minutes << "m, " << hours << "h."));
			//verbose_debug(print("delta: " << delta));
		}
		
		/**
		 * @brief Halt program execution according to desired target FPS.
		 * 
		 * @param desired_fps target FPS to cap framerate at.
		 */
		void cap_framerate(float desired_fps)
		{
			float desired_delta = (1.0f / desired_fps) * 1000.0f;	// calculate desired ms between frames from desired FPS
			if (desired_delta - delta > 0)	// if less than desired ms has passed...we must wait
			{
				float delay = std::max(desired_delta - delta, 0.0f);	// calculate the time we should delay
				//verbose_debug(println(" TRYING TO DELAY: " << desired_delta << " - " << delta << " = " << delay));

				SDL_Delay(delay);		// delay
			}
		}

	};

}

#endif /* _SDL2_LILYENGINE_CLOCK_HPP_ */

