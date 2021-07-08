# SDL2_GameEngine
Learning SDL2 and C++ by making a game engine!

The engine will mostly be a main Game class that you can inherit from:
```C++
class MyGame : public Game
{
private:
	void init();
	void update();
	void render();
	void clean();
}
```

Then running the game is as simple as:
```C++
int main(int argc, char* argv[])
{
	game = MyGame();
	return game.run();
}
```
