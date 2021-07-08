# SDL2_GameEngine
## Learning SDL2 and C++ by making a game engine!
This engine will attempt to be versatile, meaning you could make a fully featured game in a couple lines of code, or you can use certain parts of the engine that you like!  
Let's say I wanted to make a platformer game. I'll need graphics, audio, controls, maps, physics, different levels, menus, options... or I could put all of that into one simple to use PlatformerGame abstraction:
```C++
game = PlatformerGame("my-game.gameconfig");	// optional gameconfig file can have anything to edit the default PlatformerGame class
game.setPlayer("player.png");
game.setBackground("bg.png");
game.addLevels("map0*.tmx");	// adds all levels that match this! map00, map01, map02, etc
for(int level = 0; level <= 2; level++)
{
	game.addLevel(level, "map0"+level+".tmx");
}
game.run();
```
Or if I want more customization with the player or physics, I can subclass PlatformerGame and implement my own functionality into the game:
```C++
class MyPlatformerGame : public PlatformerGame
{
	// override protected methods here
}
```
Or I can construct a base game with no default functionality and write it all myself by inheriting from ```Game```!

## Features  
  
### Game Class
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

### Asset Management
The engine will have a simple system for creating game objects out of assets, with an internal resource manager:
```C++
// Create a Sprite game object (pos, size, rotation, color, blendmode, etc), with a Texture resource (internal, managed by Assets class)
Sprite* player = Assets.createSprite("img/player.png");
// Create another Sprite based on the same image! Assets class will manage this so they share a texture!
Sprite* player2 = Assets.createSprite("img/player.png");

// Audio game object (pos, volume, panning, loops), with an Audio resource
Sound* music = Assets.createSound("snd/bg-music.wav");

// TileMap game object, uses Tiled files (mapeditor.org)
TileMap* overworldMap = Assets.createTileMap("map/tile-world.tmx");	

// Stage game object, can create a Stage based on a .stage file
Stage level1 = Assets.createStage("map/level-1.stage");

// To optionally free assets before the game ends:
delete player;	// destructors will free resources
delete music;

// To free up all assets at the end of the game:
Assets.free();
```

### Stages
All of the game objects created can be added to Stages:
```C++
Stage world = Stage();	// Create a blank Stage
world.setMap();		// Set the map to be used
world.add(player);	// Add a Sprite (actor)
world.setMusic(music);	// Set the music (will play when stage becomes active)

```
