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

/**
 * @brief Calls BaseGame::run().
 */
void ExampleGame::run()
{
	BaseGame::run();
}



void ExampleGame::init() {

}

bool ExampleGame::event(SDL_Event& event) {
	return false;
}

void ExampleGame::update() {

}

void ExampleGame::render() {

}

void ExampleGame::cleanup() {

}

/**
 * @brief Frees up ExampleGame resources from memory.
 */
ExampleGame::~ExampleGame()
{
}