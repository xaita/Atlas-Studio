#ifndef __MODULE_Disk_H__
#define __MODULE_Disk_H__ 

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleDisk : public Module
{
public:
	// Constructor
	ModuleDisk(bool startEnabled);

	// Destructor
	~ModuleDisk();

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
	int disc_speed_X=0;
	int disc_speed_Y=0;
	bool muerte_subita;

	int saque = 1;
	int timer =0;
	int timer_set = 0;
	int timer_Win =300;
	int timerblock = 0;
	int ultimplayer=0;
	int score_player_1 = 0;
	int score_player_2 = 0;
	int sets_player1 = 0;
	int sets_player2 = 0;
	int sets = 0;
	int godmode = -1;
	int si = 0;



	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation2 = nullptr;

	// A set of animations
	Animation moving;
	Animation projectile;
	Animation invisible;
	Animation blocking;


	// The player's collider
	Collider* diskcollider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	void movimiento(int mov);

};

#endif //!__MODULE_Disk_H__ 