# SDL2_GameEngine
Learning SDL2 and C++ by making a game engine!

The engine will mostly be a main Game class that you can inherit from, then running the game is as simple as:
```C++
int main(int argc, char* argv[])
{
	game = new MyGame();
	game.mainloop();
	return 0;
}

```
