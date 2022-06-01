#ifndef __SCENE_COINS_H
#define __SCENE_COINS_H
#define NUM_IMAGES 316

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneCoins : public Module
{
public:
	//Constructor
	SceneCoins(bool startEnabled);

	//Destructor
	~SceneCoins();

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

	int timer;
	int frame;
};

#endif
