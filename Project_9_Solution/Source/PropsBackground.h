#ifndef __PROPS_BACKGROUND_H__
#define __PROPS_BACKGROUND_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class PropsBackground : public Module
{
public:
	//Constructor
	PropsBackground(bool startEnabled);

	//Destructor
	~PropsBackground();

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
	SDL_Texture* bgBotwall = nullptr;
	SDL_Texture* bgGoal = nullptr;
	SDL_Texture* bgGoalright = nullptr;
	SDL_Texture* bgGoalgoal = nullptr;
	SDL_Texture* bgGoalsupergoal = nullptr;
	SDL_Texture* referee = nullptr;
	SDL_Texture* bgFrisbees = nullptr; 

	Animation* currentAnimation;

	Animation refereeIdle;
	Animation refereeLookLeft;
	Animation refereeLookRight;
	//Animation refereePointRight;

	Animation frisbees;			//frisbees de l'arbitre, a terra
};

#endif