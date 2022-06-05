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

	//beach
	SDL_Texture* beachBotWall = nullptr;
	SDL_Texture* beachTopWall = nullptr;
	SDL_Texture* beachLeftGoal = nullptr;
	SDL_Texture* beachRightGoal = nullptr;
	SDL_Texture* beachLeftGoalGoal = nullptr;
	SDL_Texture* beachRightGoalGoal = nullptr;

	//concrete
	SDL_Texture* bgBotwall = nullptr;
	SDL_Texture* bgGoal = nullptr;
	SDL_Texture* bgGoalright = nullptr;
	SDL_Texture* bgGoalgoal = nullptr;
	SDL_Texture* bgGoalgoalright = nullptr;

	//lawn
	SDL_Texture* lawnBotWall = nullptr;
	SDL_Texture* lawnTopWall = nullptr;
	SDL_Texture* lawnLeftGoal = nullptr;
	SDL_Texture* lawnRightGoal = nullptr;
	SDL_Texture* lawnLeftGoalGoal = nullptr;
	SDL_Texture* lawnRightGoalGoal = nullptr;



	SDL_Texture* referee = nullptr;
	SDL_Texture* bgFrisbees = nullptr; 
	SDL_Texture* UI = nullptr;


	SDL_Rect P1WIN = { 326, 86, 110, 32 };
	SDL_Rect P2WIN = { 224, 86, 100, 32 };
	SDL_Rect P1LOSE = { 0, 54, 100, 27 };
	SDL_Rect P2LOSE = { 393, 27, 99, 27 };
	SDL_Rect SetScore0 = { 135, 27, 45, 26 };
	SDL_Rect SetScore1 = { 180, 27, 43, 26 };
	SDL_Rect SetScore2 = { 222, 27, 47, 26 };
	SDL_Rect SetScore3 = { 270, 27, 45, 26 };
	SDL_Rect SetCount = { 315, 27, 78, 26 };

	Animation* currentAnimationReferee = nullptr;

	Animation refereeIdle;
	Animation refereeLookLeft;
	Animation refereeLookRight;
	Animation refereePointLeft;
	Animation refereePointRight;
	Animation refereeNewDisk;

	Animation frisbees;
	//frisbees de l'arbitre, a terra
	int timersetcount = 189;
	int timerrefree = 0;

	bool agafaDisc;
};

#endif