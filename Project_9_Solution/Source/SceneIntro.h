#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//Constructor
	SceneIntro(bool startEnabled);

	//Destructor
	~SceneIntro();

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

	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* UI = nullptr;
	SDL_Texture* bgCredits = nullptr;

	SDL_Rect P1 = { 359, 11, 20, 16 };
	SDL_Rect P2 = { 392, 11, 22, 16 };

	// Sound effects indices
	uint select = 0;
	uint Coinfx = 0;
	uint JapanSelectedfx = 0;
	uint GermanySelectedfx = 0;
	uint KoreanSelectedfx = 0;

	char selectPlayer1 = '1';
	char xdselectPlayer1 = '1';

	char selectPlayer2;
	char xdselectPlayer2;
	int selecttimer;
	int x1;
	int y1;
	int x2;
	int y2;
	bool Readyp1;
	bool Readyp2;
};

#endif