#ifndef __MODULE_PLAYER2_H__
#define __MODULE_PLAYER2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
public:
	// Constructor
	ModulePlayer2(bool startEnabled);

	// Destructor
	~ModulePlayer2();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation rightidleAnim;
	Animation leftidleAnim;
	Animation rightidleFrisbee;
	Animation uprightidleFrisbee;
	Animation downrightidleFrisbee;
	Animation upAnim;
	Animation upleftAnim;
	Animation downAnim;
	Animation downleftAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation shooting;
	Animation ulti;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
	uint discFx = 0;
	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

};

#endif //!__MODULE_PLAYER2_H__