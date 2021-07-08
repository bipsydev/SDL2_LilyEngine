# SDL2_GameEngine
Learning SDL2 and C++ by making a game engine!

The engine will have a simple system for creating game objects out of assets, with an internal resource manager:
```C++
Sprite* player = Assets.createSprite("img/player.png");	// Sprite game object (pos, size, rotation, color, blendmode, etc), with a Texture resource (internal, managed by Assets class)
Sound* music = Assets.createSound("snd/bg-music.wav");	// Audio game object (pos, volume, panning, loops), with an Audio resource
TileMap* overworldMap = Assets.createTileMap("map/tile-world.tmx");	// TileMap game object, uses Tiled files (mapeditor.org)
StageMap* level1 = Assets.createStageMap("map/level-1.stage");		// StageMap game object, can create a Stage based on a StageMap, also can save a Stage as a .stage file

// To optionally free assets before the game ends:
delete player;	// destructors will free resources
delete music;

// To free up all assets at the end of the game:
Assets.free();
```

All of the assets created can be added to Stages:
```C++
Stage world = Stage();
world.add(player);
world.setMusic(music);

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
