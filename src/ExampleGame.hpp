/*	ExampleGame.hpp	-	Heather Crawford	-	07-09-2021
Example SDL2 Game.
*/
#pragma once
#ifndef _SDL2LE_EXAMPLEGAME_HPP_
#define _SDL2LE_EXAMPLEGAME_HPP_

#include <lilyengine/BaseGame.hpp>

class ExampleGame: public BaseGame
{
private:
public:
	ExampleGame(const char* title = "ExampleGame", int width = 640, int height = 480, bool run_instantly = false);
	~ExampleGame();

	void run() override;
};

#endif /* _SDL2LE_EXAMPLEGAME_HPP_ */