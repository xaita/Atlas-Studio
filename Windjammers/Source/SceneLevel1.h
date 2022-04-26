#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgBotwall = nullptr;
	SDL_Texture* bgTopwall = nullptr;
	SDL_Texture* bgExtremetopwall = nullptr;
	SDL_Texture* bgExtremetopwallright = nullptr;
	SDL_Texture* bgNet = nullptr;
	SDL_Texture* bgGoal = nullptr;
	SDL_Texture* bgGoalright = nullptr;
	SDL_Texture* bgGoalgoal = nullptr;
	SDL_Texture* bgGoalsupergoal = nullptr;


	Animation* currentAnimation = nullptr;

	Animation spectators;


};

#endif