/**
 * @file ExampleGame.cpp
 * @author lilitharcana (lilithalicecrawford@gmail.com)
 * @brief Implements the ExampleGame class.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "ExampleGame.hpp"
#include <iostream>

/**
 * @brief Construct a new Example Game object
 * Sets window title, size, and autorun.
 */
ExampleGame::ExampleGame(std::string title)
: BaseGame(title.c_str(), 640, 480, false)
{
}

void ExampleGame::run()
{
	BaseGame::run();
}



bool ExampleGame::init()
{
	// Load a text box
	textbox = new LilyEngine::LTextBox(getFont(), "Here is some default text!");
	return true;
}

bool ExampleGame::event(SDL_Event& event)
{
	return false;
}

void ExampleGame::update()
{

}

void ExampleGame::render()
{
	textbox->render(getRenderer());
}

void ExampleGame::cleanup()
{
	// free resources
	delete textbox;
}

/**
 * @brief Frees up ExampleGame resources from memory.
 */
ExampleGame::~ExampleGame()
{
}