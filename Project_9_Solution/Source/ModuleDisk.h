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
	float disc_speed_X = 0;
	float disc_speed_Y = 0;
	bool muerte_subita;

	int saque = -1;
	int timer = 0;
	int timer_set = 0;
	int timer_Win = 300;
	int timerblock = 0;
	int ultimplayer = 0;
	int score_player_1 = 0;
	int score_player_2 = 0;
	int sets_player1 = 0;
	int sets_player2 = 0;
	int sets = 0;
	bool godmode;
	int si = 0;
	int volea_x;
	int volea_y;

	//int volea = 0;

	bool bloqueig;
	bool onair;
	bool volea;


	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* texturevolea = nullptr;
	SDL_Texture* marca = nullptr;


	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation2 = nullptr;


	// A set of animations
	Animation moving;
	Animation projectile;
	Animation invisible;
	Animation blocking;
	Animation idle;
	Animation voleaanim;

	uint blockfx = 0;
	uint catchfx = 0;
	uint onairfx = 0;

	//sfx arbitre
	uint Pts2 = 0;
	uint Pts3 = 0;
	uint Pts5 = 0;
	uint CongratulationsWinner = 0;
	uint ExcelentGame = 0;
	uint FinalRound = 0;
	uint GameSet = 0;
	uint GetReady = 0;
	uint GoodGame = 0;
	uint Miss = 0;
	uint Out = 0;
	uint Round1 = 0;
	uint Round2 = 0;
	uint Round3 = 0;
	uint Round4 = 0;
	uint Round5 = 0;
	uint Set = 0;
	uint Spear = 0;
	uint Strike = 0;
	uint WellDone = 0;
	uint Wow = 0;
	uint Ya = 0;

	// The player's collider
	Collider* diskcollider = nullptr;
	Collider* super_zone_collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	void movimiento(int mov);

};

#endif //!__MODULE_Disk_H__ 