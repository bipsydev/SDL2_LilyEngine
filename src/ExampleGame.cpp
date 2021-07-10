/*	ExampleGame.cpp	-	Heather Crawford	-	07-09-2021

*/
#include "ExampleGame.hpp"
#include <iostream>

ExampleGame::ExampleGame(const char* title, int width, int height, bool run_instantly)
: BaseGame(title, width, height, run_instantly)
{
}

void ExampleGame::run()
{
	BaseGame::run();
}

ExampleGame::~ExampleGame()
{
}