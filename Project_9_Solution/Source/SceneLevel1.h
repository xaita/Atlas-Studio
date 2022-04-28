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
	
	// Textures del bg
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTopwall = nullptr;
	SDL_Texture* bgExtremetopwall = nullptr;
	SDL_Texture* bgExtremetopwallright = nullptr;
	SDL_Texture* bgNet = nullptr;
	SDL_Texture* UI = nullptr;
	

	//arbitre
	SDL_Texture* referee = nullptr;
	//SDL_Texture* bgFrisbees = nullptr;

	SDL_Rect score0 = { 16, 11, 13, 11};
	SDL_Rect score1 = { 28, 11, 3, 11 };
	SDL_Rect score2 = { 31, 11, 13, 11 };
	SDL_Rect score3 = { 44, 11, 12, 11 };
	SDL_Rect score4 = { 56, 11, 13, 11 };
	SDL_Rect score5 = { 69, 11, 13, 11 };
	SDL_Rect score6 = { 82, 11, 13, 11 };
	SDL_Rect score7 = { 95, 11, 12, 11 };
	SDL_Rect score8 = { 107, 11, 13, 11 };
	SDL_Rect score9 = { 120, 11, 13, 11 };
	SDL_Rect scoreG = { 133, 11, 13, 11 };
	SDL_Rect scoreO = { 16, 11, 13, 11 };

	SDL_Rect Set_1 = { 160, 300, 160, 56 };
	SDL_Rect Set_2 = { 320, 300, 160, 56 };
	SDL_Rect Set_Final = { 0, 300, 160, 56 };




	

	Animation* currentAnimation = nullptr;

	Animation spectators;
	Animation refereeAnim;
	Animation score;


};

#endif