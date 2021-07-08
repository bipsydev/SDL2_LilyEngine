# SDL2_GameEngine
Learning SDL2 and C++ by making a game engine!

The engine will have a simple system for creating game objects out of assets, with an internal asset manager:
```C++
Sprite* player = Assets.createSprite("img/player.png");
Audio* music = Assets.createAudio("snd/bg-music.wav");

// To optionally free assets before the game ends:
delete player;
delete music;

// To free up all assets at the end of the game:
Assets.free();
```

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
