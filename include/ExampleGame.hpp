/**
 * @file ExampleGame.hpp
 * @author lilitharcana (lilithalicecrawford@gmail.com)
 * @brief Example template game for the game engine.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#ifndef _SDL2_LILYENGINE_EXAMPLEGAME_HPP_
#define _SDL2_LILYENGINE_EXAMPLEGAME_HPP_

#include <SDL2_LilyEngine.hpp>

class ExampleGame: public BaseGame
{
private:
public:
	ExampleGame();
	~ExampleGame();

	void run() override;
};

#endif /* _SDL2_LILYENGINE_EXAMPLEGAME_HPP_ */