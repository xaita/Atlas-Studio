#ifndef __SCENE_INTRO_SNK_H__
#define __SCENE_INTRO_SNK_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntroSNK : public Module
{
public:
	//Constructor
	SceneIntroSNK(bool startEnabled);

	//Destructor
	~SceneIntroSNK();

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
	SDL_Texture* bgTexture[128];
	SDL_Texture* bgSNK = nullptr;

	Animation* currentAnimation = nullptr;

	Animation SNK;
	int timer;
	int frame;
};

#endif
