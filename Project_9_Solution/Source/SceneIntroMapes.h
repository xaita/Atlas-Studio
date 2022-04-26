#ifndef __SCENE_INTRO_MAPES_H__
#define __SCENE_INTRO_MAPES_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntroMapes : public Module
{
public:
	//Constructor
	SceneIntroMapes(bool startEnabled);

	//Destructor
	~SceneIntroMapes();

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
};
<<<<<<< HEAD
#endif
=======

#endif
>>>>>>> main
