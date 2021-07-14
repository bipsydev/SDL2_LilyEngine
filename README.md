# `SDL2_LilyEngine` by _lilitharcana_
###### *Check the* [docs!](https://lilitharcana.github.io/SDL2_LilyEngine)
> *I'm learning SDL2 and C++ by making a game engine!*

__`SDL2_LilyEngine`__ aims to be an educational high-level OOP wrapper framework for the SDL2 graphics library in C++!  
At its core, __`SDL2_LilyEngine`__ will be a *static library* of components for easy SDL operations. A *framework* for creating your own game class via inheritance can be used, or you can use the libraries individually. Additionally in the future, I plan to make a *graphical interface* to the engine that outputs C++ code!  

----------------

It will provide one main abstract `LilyEngine::BaseGame` class with 5 pure virtual methods:
```C++
namespace LilyEngine {
	class BaseGame {
	protected:
		// initialize game objects, global variables, set inputs, load resources, configure systems...
		virtual void init(string title) = 0;

		// Main game loop, runs every frame:
		virtual bool event(SDL_Event* event) = 0;	// react to an event passed to the game, and return true if the event was caught
		virtual void update() = 0;			// update game variables based in events/input/etc
		virtual void render() = 0;			// render graphics output for the frame

		// save the game if needed, unload textures, quit systems
		virtual void cleanup() = 0;
	};
}
```
This way, you can inherit from `BaseGame` and make your own `MyWackyGame` class overriding the virtual methods, and then run the game in your main method:
```C++
int main(int argv, char** args) {
	MyWackyGame* game = new MyWackyGame();
	int exit_val = game->run();
	delete game;
	return exit_val;
}
```
Or for even better shorthand:
```C++
int main(int argv, char** args) {
	return MyWackyGame::factoryRun();
}
```
There will also be protected class member subsystems you can use modularly inside your game subclass:
```C++
namespace LilyEngine {
	class BaseGame {
	protected:
		LilyEngine::Clock clock;		// holds game time, frame number, delta time, can cap fps or enable vsync
		LilyEngine::StageManager stageManager;	// manages your Stages, sets the active stage and updates it with all its actors
		LilyEngine::Graphics graphics;		// graphics loading/rendering module, creates sprites, fonts, and shape drawing
		LilyEngine::Audio audio;		// audio module for loading/playing sounds
		LilyEngine::Input input;		// input module for querying controls
	};
}
```
The *stage* and *actor* system is used to create game actors and add them to a stage. The `LilyEngine::Actor` abstract class can be inherited to create your own game object classes. The `LilyEngine::Stage` class can be filled with Actors, subsequently saved or loaded, and hold cameras and room information. The `LilyEngine::StageManager` controls the current stage, keeps loaded stages running, and can script stages/scenes together and run/save them!
```C++
class MyPlayerActor: public LilyEngine::SpriteActor {
	MyPlayerActor(): LilyEngine::SpriteActor("images/player.png") {
	}
	
	void enterStage() override {
		setPosition(LilyEngine::POS_WINDOW_CENTER);
	}
	void update() override {
		speed.x += getGame().clock.delta;
	}
}

// ... then, at some point during inside your game's init() or update():
Stage level1 = stageManager.loadfromMap("maps/level1.tmx");
level1.enterWithFocus(MyPlayerActor());
stageManager.setActive(level1);
// now the stage will automatically be updating during event(), update(), and render()!

// ... when the game is closed/exited:
stageManager.saveAll("saves/save1.gamestate");
// and when the game is reopened and needs to reload:
stageManager.loadAll("saves/save1.gamestate");

```

--------------------------------------------------------
# Plan Overview
>This engine will attempt to be versatile, meaning you could make a fully featured barebones game in a couple lines of code, or you can use certain parts of the engine that you like!

Let's say I wanted to make a platformer game. I'll need graphics, audio, controls, maps, physics, different levels, menus, options... or I could put all of that into one simple to use PlatformerGame class:
```C++
PlatformerGame game = PlatformerGame("my-game.gameconfig");	// optional .gameconfig file can have anything to edit the default PlatformerGame class

// Use PlatformerGame's public methods to set it up how you like!
game.setPlayer("player.png");
game.setBackground("bg.png");
game.addLevels("map0*.tmx");	// adds all levels that match this! map00, map01, map02, etc

// run and close the game!
game.run();
```
Or if I want more customization with the player or physics, I can subclass PlatformerGame and implement my own functionality into the game:
```C++
class MyPlatformerGame: public PlatformerGame
{
public:
    MyPlatformerGame(): PlatformerGame("my-game.gameconfig")
    {
        setPlayer("player.png");
	setBackground("bg.png");
	addLevels("map0*.tmx");
    }
protected:
    // override protected methods from PlatformerGame or Game here to change internal functionality!
}
```
Or I can construct a base game with no default functionality and write it all myself by inheriting from ```Game```!

## Planned Features

### Game Class
The engine will mostly be a main ```Game``` class that you can inherit from:
```C++
class MyGame: public Game
{
protected:
    void init();	// Initialize your game objects/assets
    void event();	// React to user input or other events
    void update();	// Update game logic/physics
    void render();	// draw to the game framebuffer
    void clean();	// optional, free up all assets
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
##### Virtual, Protected Methods
> ```Game``` class and it's subclass templates (like ```PlatformerGame```) all contain many protected virtual methods that can be overridden. This way, the internal functionality can always be changed at specific points!

### Asset Management
The engine will have a simple system for creating ```GameObject```s out of assets, with an internal ```Resource``` manager:
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
All of the game objects created can be added to ```Stage```s:
```C++
Stage world = Stage();	// Create a blank Stage
world.setMap();		// Set the map to be used
world.add(player);	// Add a Sprite (actor)
world.setMusic(music);	// Set the music (will play when stage becomes active)
```
Stages can be set to automatically update, render, and catch events for all of its actors:
```C++
game.setStage(world);
```

### Event Handling
Lambda functions can be attached as an ```EventHandler``` to any ```GameObject```, ```Stage```, or ```Game```! 
```C++
player.addEvent<KeyboardEvent>(
    [&player] (KeyboardEvent event) {
    	if(event.keycode == "K_SPACE")
	{
	    player.jump();
	    player.addVelocity(-5.0f, 0f);
	}
    }
);
```
