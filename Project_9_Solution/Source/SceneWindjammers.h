#ifndef __SCENE_WINDJAMMERS_H__
#define __SCENE_WINDJAMMERS_H__
#define NUM_IMAGES 64

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneWindjammers : public Module
{
public:
	//Constructor
	SceneWindjammers(bool startEnabled);

	//Destructor
	~SceneWindjammers();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture[NUM_IMAGES];
	SDL_Texture* bgFoto = nullptr;


	uint Coinfx = 0;

	int timer;
	int frame;
};

#endif
