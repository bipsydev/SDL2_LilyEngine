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

class ExampleGame: public LilyEngine::BaseGame
{
private:
	LilyEngine::LTextBox* textbox;
	
public:
	ExampleGame(std::string title = "This is an Example Game!");
	~ExampleGame();

	void run() override;

	bool init() override;
	bool event(SDL_Event& event) override;
	void update() override;
	void render() override;
	void cleanup() override;

};

#endif /* _SDL2_LILYENGINE_EXAMPLEGAME_HPP_ */