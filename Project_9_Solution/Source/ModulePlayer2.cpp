#include "ModulePlayer2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include"ModuleDisk.h"
#include "SDL/include/SDL.h"
#include "SceneIntro.h"
#include <chrono>
#include <thread>

#include <stdio.h>

using namespace std::chrono;
using namespace std::this_thread;

ModulePlayer2::ModulePlayer2(bool startEnabled) : Module(startEnabled)
{
	
	

	//en les diagonals a la dreta l'animació és la mateixa que moure's cap a dalt o baix.

}

ModulePlayer2::~ModulePlayer2()
{

}

bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	switch (App->sceneIntro->xdselectPlayer2) {

	case '1':
		correcciox = 0;
		correccioy = 0;
		texture = App->textures->Load("Assets/Sprites/Characters/Hiromi Mita/JapaneseSpriteSheedCanviL2P2.png");
		rightidleAnim.PushBack({ 393, 103 , 23, 36 });// frame 1
		rightidleAnim.PushBack({ 370, 103 , 23, 35 });// frame 2
		rightidleAnim.PushBack({ 347, 103 , 23, 36 });// frame 3
		rightidleAnim.PushBack({ 323, 103 , 24, 36 });// frame 4
		rightidleAnim.PushBack({ 299, 103 , 24, 35 });// frame 5
		rightidleAnim.PushBack({ 275, 103 , 24, 36 });// frame 6
		rightidleAnim.PushBack({ 251, 103 , 24, 39 });// frame 7
		rightidleAnim.PushBack({ 227, 103 , 24, 37 });// frame 8
		rightidleAnim.loop = true;
		rightidleAnim.speed = 0.08f;

		leftidleAnim.PushBack({ 393, 359 , 23, 36 });// frame 1
		leftidleAnim.PushBack({ 370, 359 , 23, 35 });// frame 2
		leftidleAnim.PushBack({ 347, 359 , 23, 36 });// frame 3
		leftidleAnim.PushBack({ 323, 359 , 24, 36 });// frame 4
		leftidleAnim.PushBack({ 299, 359 , 24, 35 });// frame 5
		leftidleAnim.PushBack({ 274, 359 , 25, 36 });// frame 6
		leftidleAnim.PushBack({ 250, 359 , 24, 39 });// frame 7
		leftidleAnim.PushBack({ 227, 359 , 23, 37 });// frame 8
		leftidleAnim.loop = true;
		leftidleAnim.speed = 0.08f;

		// move upwards
		upAnim.PushBack({ 150, 447, 30, 40 });// frame 1
		upAnim.PushBack({ 120, 447, 30, 51 });// frame 2
		upAnim.PushBack({ 90, 447, 30, 50 });// frame 3
		upAnim.PushBack({ 60, 447, 30, 40 });// frame 4
		upAnim.PushBack({ 30, 447, 30, 53 });// frame 5
		upAnim.PushBack({ 0, 447, 30, 50 });// frame 6
		upAnim.loop = true;
		upAnim.speed = 0.1f;

		// Move down
		downAnim.PushBack({ 240, 404, 29, 43 });// frame 1
		downAnim.PushBack({ 208, 404, 32, 38 });// frame 2
		downAnim.PushBack({ 179, 404, 29, 35 });// frame 3
		downAnim.PushBack({ 155, 404, 24, 41 });// frame 4
		downAnim.PushBack({ 125, 404, 30, 38 });// frame 5
		downAnim.PushBack({ 94, 404, 31, 34 });// frame 6
		downAnim.loop = true;
		downAnim.speed = 0.1f;

		// move right 
		rightAnim.PushBack({ 454, 148, 45, 32 }); // frame 1
		rightAnim.PushBack({ 426, 148, 28, 33 }); // frame 2
		rightAnim.PushBack({ 385, 148, 41, 36 }); // frame 3
		rightAnim.PushBack({ 339, 148, 46, 29 }); // frame 4
		rightAnim.PushBack({ 310, 148, 29, 36 }); // frame 5
		rightAnim.PushBack({ 269, 148, 41, 35 }); // frame 6
		rightAnim.loop = true;
		rightAnim.speed = 0.1f;

		// move left
		leftAnim.PushBack({ 455, 404, 45, 32 });
		leftAnim.PushBack({ 427, 404, 28, 33 });
		leftAnim.PushBack({ 386, 404, 40, 36 });
		leftAnim.PushBack({ 340, 404, 45, 29 });
		leftAnim.PushBack({ 311, 404, 28, 36 });
		leftAnim.PushBack({ 270, 404, 40, 35 });
		leftAnim.loop = true;
		leftAnim.speed = 0.1f;

		// rightdash
		rightdash.PushBack({ 43,148,51,24 });
		rightdash.PushBack({ 0,148,43,31 });
		rightdash.PushBack({ 474,103,30,33 });
		rightdash.loop = false;
		rightdash.speed = 0.1f;

		leftdash.PushBack({ 43,404,51,24 });
		leftdash.PushBack({ 0,404,43,31 });
		leftdash.PushBack({ 474,359,30,33 });
		leftdash.loop = false;
		leftdash.speed = 0.1f;


		updash.PushBack({ 433,191,25,53 });
		updash.PushBack({ 402,191,31,24 });
		updash.PushBack({ 374,191,28,33 });
		updash.loop = false;
		updash.speed = 0.1f;

		downdash.PushBack({ 277,46,25,57 });
		downdash.PushBack({ 245,46,32,49 });
		downdash.PushBack({ 213,46,32,41 });

		downdash.loop = false;
		downdash.speed = 0.1f;

		rightupdash.PushBack({ 329,191,45,41 });
		rightupdash.PushBack({ 297,191,32,30 });
		rightupdash.PushBack({ 270,191,27,37 });

		rightupdash.loop = false;
		rightupdash.speed = 0.1f;

		rightdowndash.PushBack({ 177,46,36,48 });
		rightdowndash.PushBack({ 140,46,37,40 });
		rightdowndash.PushBack({ 107,46,33,35 });

		rightdowndash.loop = false;
		rightdowndash.speed = 0.1f;

		leftupdash.PushBack({ 329,447,45,41 });
		leftupdash.PushBack({ 297,447,32,30 });
		leftupdash.PushBack({ 270,447,27,37 });

		leftupdash.loop = false;
		leftupdash.speed = 0.1f;

		leftdowndash.PushBack({ 177,302,36,48 });
		leftdowndash.PushBack({ 140,302,37,40 });
		leftdowndash.PushBack({ 107,302,33,35 });

		leftdowndash.loop = false;
		leftdowndash.speed = 0.1f;




		//animation shooting
		shooting.PushBack({ 73, 302, 34, 40 });// frame 1
		shooting.PushBack({ 37, 302, 36, 38 });// frame 2
		shooting.PushBack({ 0, 302, 37, 40 });// frame 3
		shooting.PushBack({ 459, 256,	33,	41 });// frame 4
		shooting.PushBack({ 432, 256,	27,	46 });// frame 5
		shooting.PushBack({ 409, 256,	23,	43 });// frame 6


		shooting.loop = false;
		shooting.pingpong = false;
		shooting.speed = 0.2f;


		//Animation idle before shooting
		rightidleFrisbee.PushBack({ 0, 511, 47, 48 });
		rightidleFrisbee.PushBack({ 48, 511, 47, 45 });
		rightidleFrisbee.PushBack({ 96, 511, 47, 48 });
		rightidleFrisbee.PushBack({ 144, 511, 47, 48 });
		rightidleFrisbee.PushBack({ 192, 511, 47, 48 });
		rightidleFrisbee.loop = true;
		rightidleFrisbee.speed = 0.08f;
		uprightidleFrisbee.PushBack({ 417, 517, 46, 42 });
		downrightidleFrisbee.PushBack({ 371, 515, 46, 44, });

		blockanim.PushBack({ 49, 256, 28,	35 });
		blockanim.PushBack({ 25, 256, 24, 35 });
		blockanim.PushBack({ 0,  256, 25,	35 });
		blockanim.loop = false;
		blockanim.speed = 0.25f;

		charge_ult.PushBack({ 445,103,29,45 });
		charge_ult.PushBack({ 416,103,29,44 });
		charge_ult.loop = false;
		charge_ult.speed = 0.1f;
		break;

	case '2':

		texture = App->textures->Load("Assets/Sprites/Characters/Beeho Yoo/beehoYooSpriteSheet_player2.png");
		correcciox = -20;
		correccioy = -18;
		//idleLAnim
		for (int i = 0; i < 8; i++) {
			leftidleAnim.PushBack({ 462 + (i * 66), 462, 66, 66 });
		}
		leftidleAnim.loop = true;
		leftidleAnim.speed = 0.1f;

		//idleRAnim
		for (int i = 0; i < 8; i++) {
			rightidleAnim.PushBack({ 198 + (i * 66), 0, 66, 66 });
		}
		rightidleAnim.loop = true;
		rightidleAnim.speed = 0.1f;

		// Move Right

		rightAnim.PushBack({ 726, 0, 66, 66 });
		rightAnim.PushBack({ 792, 0, 66, 66 });
		rightAnim.PushBack({ 858, 0, 66, 66 });
		rightAnim.PushBack({ 924, 0, 66, 66 });
		rightAnim.PushBack({ 990, 0, 66, 66 });
		rightAnim.PushBack({ 1056, 0, 66, 66 });

		rightAnim.loop = true;
		rightAnim.speed = 0.1f;

		//Move Left
		leftAnim.PushBack({ 1122, 0, 66, 66 });
		leftAnim.PushBack({ 0, 66, 66, 66 });
		leftAnim.PushBack({ 66, 66, 66, 66 });
		leftAnim.PushBack({ 132, 66, 66, 66 });
		leftAnim.PushBack({ 198, 66, 66, 66 });
		leftAnim.PushBack({ 264, 66, 66, 66 });

		leftAnim.loop = true;
		leftAnim.speed = 0.1f;


		
		for (int i = 0; i < 6; i++) {
			downAnim.PushBack({ 66 + (i * 66), 528, 66, 66 });
		}
		downAnim.loop = true;
		downAnim.speed = 0.1f;

		//Move Up Head Left
		for (int i = 0; i < 6; i++) {
			upAnim.PushBack({ 462 + (i * 66), 528, 66, 66 });
		}
		upAnim.loop = true;
		upAnim.speed = 0.1f;

		//Idle Disk

		for (int i = 0; i < 8; i++) {
			rightidleFrisbee.PushBack({ 660 + (i * 66), 792, 66, 66 });
		}
		rightidleFrisbee.loop = true;
		rightidleFrisbee.speed = 0.075f;

		//Lanzamiento Disco
		for (int i = 5; i >= 0; i--) {
			shooting.PushBack({ 396 + (i * 66), 858, 66, 66 });
		}
		shooting.loop = false;
		shooting.speed = 0.3f;

		//Dash derecho
		rightdash.PushBack({ 1122, 66, 66, 66 });
		for (int i = 0; i < 3; i++) {
			rightdash.PushBack({ 0 + (i * 66), 132, 66, 66 });
		}
		rightdash.loop = false;
		rightdash.speed = 0.15f;

		//Dash izquierdo
		leftdash.PushBack({ 0, 528, 66, 66 });
		leftdash.PushBack({ 1122, 594, 66, 66 });
		leftdash.PushBack({ 1056, 594, 66, 66 });
		leftdash.PushBack({ 989, 594, 66, 66 });

		leftdash.loop = false;
		leftdash.speed = 0.15f;

		//Dash arriba
		for (int i = 0; i < 3; i++) {
			updash.PushBack({ 198 + (i * 66), 132, 66, 66 });
		}
		updash.loop = false;
		updash.speed = 0.15f;

		//Dash abajo
		downdash.PushBack({ 726, 132, 66, 66 });
		downdash.PushBack({ 792, 132, 66, 66 });
		downdash.PushBack({ 1122, 132, 66, 66 });
		downdash.PushBack({ 132, 198, 66, 66 });
		downdash.loop = false;
		downdash.speed = 0.15f;

		//Win
		/*for (int i = 0; i < 3; i++) {
			win.PushBack({ 132 + (i * 66), 264, 66, 66 });
		}
		win.loop = true;
		win.speed = 0.05f;*/

		//Lose
		/*for (int i = 0; i < 6; i++) {
			lose.PushBack({ 330 + (i * 66), 264, 66, 66 });
		}
		lose.loop = true;
		lose.speed = 0.05f;*/

		//Dash diagonalUpRight
		rightupdash.PushBack({ 462, 132, 66, 66 });
		rightupdash.PushBack({ 528, 132, 66, 66 });
		rightupdash.PushBack({ 594, 132, 66, 66 });
		rightupdash.PushBack({ 660, 132, 66, 66 });

		rightupdash.loop = false;
		rightupdash.speed = 0.15f;

		//Dash diagonalDownRight
		rightdowndash.PushBack({ 198, 198, 66, 66 });
		rightdowndash.PushBack({ 264, 198, 66, 66 });
		rightdowndash.PushBack({ 330, 198, 66, 66 });
		rightdowndash.PushBack({ 396, 198, 66, 66 });
		rightdowndash.loop = false;
		rightdowndash.speed = 0.15f;

		//Dash diagonalDownLeft
		for (int i = 3; i >= 0; i--) {
			leftdowndash.PushBack({ 726 + (i * 66), 660, 66, 66 });
		}
		leftdowndash.loop = false;
		leftdowndash.speed = 0.15f;

		//Dash diagonalUpLeft
		for (int i = 3; i >= 0; i--) {
			leftupdash.PushBack({ 462 + (i * 66), 594, 66, 66 });
		}
		leftupdash.loop = false;
		leftupdash.speed = 0.15f;

		blockanim.PushBack({ 396, 726, 66, 66});
		blockanim.PushBack({ 330, 726, 66, 66 });
		blockanim.loop = false;
		blockanim.speed = 0.2f;

		charge_ult.PushBack({ 264, 726, 66, 66 });
		charge_ult.PushBack({ 198, 726, 66, 66 });
		charge_ult.PushBack({ 132, 726, 66, 66 });
		charge_ult.loop = false;
		charge_ult.speed = 0.1f;

		downrightidleFrisbee.PushBack({ 0, 792, 66, 66 });
		uprightidleFrisbee.PushBack({ 462, 792, 66, 66 });

		break;
	}
	bool ret = true;

	currentAnimation = &leftidleAnim;

	tossfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Toss.wav");
	chargefx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Hiromi Mita/HiromiCharge.wav");
	hitfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Hiromi Mita/HiromiHit.wav");
	powerphrasefx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Hiromi Mita/HiromiPowerPhrase.wav");
	powersoundfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Hiromi Mita/HiromiPowerSound.wav");
	setwinfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Hiromi Mita/HiromiSetWin.wav");
	lobfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Lob.wav");


	position.x = 240;
	position.y = 112;
	timer_ult = 40;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 27, 31 }, Collider::Type::PLAYER2, this);
	
	
	blockup == true;

	ultimadireccio2 = 1; //1=esquerra 2=dreta
	podermoverse2 = 0;
	return ret;
}

Update_Status ModulePlayer2::Update()
{

	// Moving the player with the camera scroll
	App->player2->position.x += 0;

	if (dashtimer2 == 0) {

		dashup2 = false;
	}

	if (dashtimer2 > 0) {
		dashtimer2--;
	}
	if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_IDLE) {
		blocktimer = 0;
	}
	if (personatgedisc2 == -1)
	{
		if (App->input->keys[SDL_SCANCODE_O] != Key_State::KEY_REPEAT && dashup2 == false) {
			dashup2 = true;

		}
		if (App->disk->saque == 0) {
			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && position.x > 162)
			{
				position.x -= speed;

				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN && dashup2 == true) {
					dashtimer2 = 15;

				}
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					position.x -= 3 * speed;

					currentAnimation = &leftdash;
				}
				else if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
				}
				if (currentAnimation != &leftdash) {
					leftdash.Reset();
				}
				ultimadireccio2 = 1;
			}

			if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && position.x < 274)
			{
				position.x += speed;

				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN && dashup2 == true) {
					dashtimer2 = 15;

				}
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					position.x += 3 * speed;

					currentAnimation = &rightdash;
				}

				else if (currentAnimation != &rightAnim) 
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					
				}
				if (currentAnimation != &rightdash) {
					rightdash.Reset();
				}
				ultimadireccio2 = 2;
			}
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && position.y < 174)
			{
				position.y += speed;
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN && dashup2 == true) {
					dashtimer2 = 15;

				}
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					position.y += 3 * speed;

					currentAnimation = &downdash;
				}
				else if (currentAnimation != &downAnim && App->input->keys[SDL_SCANCODE_LEFT] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] != Key_State::KEY_REPEAT)
				{
					downAnim.Reset();
					currentAnimation = &downAnim;
				}
				if (currentAnimation != &downdash) {
					downdash.Reset();
				}
			}
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
			{
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					currentAnimation = &rightdowndash;
				}
				else if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					
				}
				ultimadireccio2 = 2;
				if (currentAnimation != &rightdowndash) {
					rightdowndash.Reset();
				}
			}
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
			{
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					currentAnimation = &leftdowndash;
				}
				else if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
				}
				ultimadireccio2 = 1;
				if (currentAnimation != &leftdowndash) {
					leftdowndash.Reset();
				}
			}
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT )
			{
				position.y -= speed;
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN && dashup2 == true) {
					dashtimer2 = 15;

				}
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					position.y -= 3 * speed;
					currentAnimation = &updash;
				}
				else if (currentAnimation != &upAnim && App->input->keys[SDL_SCANCODE_LEFT] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] != Key_State::KEY_REPEAT)
				{
					upAnim.Reset();
					currentAnimation = &upAnim;
				}
				if (currentAnimation != &updash) {
					updash.Reset();
				}
			}
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
			{
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					currentAnimation = &rightupdash;
				}
				else if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					
				}
				ultimadireccio2 = 2;
				if (currentAnimation != &rightupdash) {
					rightupdash.Reset();
				}
			}
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
			{
				if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && dashup2 == true)
				{
					currentAnimation = &leftupdash;
				}
				else if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
					
				}
				ultimadireccio2 = 1;
				if (currentAnimation != &leftupdash) {
					leftupdash.Reset();
				}
			}
			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && currentAnimation != &shooting) {

				currentAnimation = &leftidleAnim;

			}
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && currentAnimation != &shooting) {

				currentAnimation = &leftidleAnim;
			}

			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_IDLE
				&& ultimadireccio2 == 2)
			{
				currentAnimation = &rightidleAnim;
			}
			    

			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
				&& ultimadireccio2 == 1)
				{
					if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_REPEAT && blocktimer < 20) {

						blocktimer++;
						blockdisk = true;

						if (currentAnimation != &blockanim && currentAnimation != &shooting)

						{
							blockanim.Reset();
							currentAnimation = &blockanim;

						}

					}

					if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_IDLE || blocktimer >= 20) {

						blockdisk = false;

						if (currentAnimation != &charge_ult) {
							currentAnimation = &leftidleAnim;
						}
					}
			}
		}

		if (App->disk->saque == 2 || App->disk->saque == 1) {

			currentAnimation = &leftidleAnim;

		}

	}






	if (personatgedisc2 == 1) {


		currentAnimation = &rightidleFrisbee;
		if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {

			App->audio->PlayFx(tossfx, 0);


		}
		ultimadireccio2 = 1;
		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{

			currentAnimation = &uprightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {


				currentAnimation = &shooting;
				App->disk->currentAnimation2 = &App->disk->moving;
				App->disk->disc_speed_X = -5;
				App->disk->disc_speed_Y = -2;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 2;

			}
			if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)	//volea
			{

				shooting.Reset();
				currentAnimation = &shooting;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 1;
				App->disk->volea_x = App->disk->position.x - 120;
				App->disk->volea_y = App->disk->position.y - (120 / 2.5) - 16;
				if (App->disk->volea_y <= 30) {
					App->disk->disc_speed_X = -2.0;
					App->disk->volea = true;
					App->disk->volea_y = App->disk->position.y;

					App->audio->PlayFx(lobfx, 0);

				}
				else {
					App->disk->disc_speed_X = -2.0;
					App->disk->disc_speed_Y = -1;
					App->disk->volea = true;

					App->audio->PlayFx(lobfx, 0);
				}
			}
		}

		else if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{

			currentAnimation = &uprightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {

				currentAnimation = &shooting;
				App->disk->currentAnimation2 = &App->disk->moving;

				App->disk->disc_speed_X=-3;
				App->disk->disc_speed_Y = -6;

				personatgedisc2 = -1;

				App->disk->ultimplayer = 2;/////
			}
			if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)	//volea
			{

				shooting.Reset();
				currentAnimation = &shooting;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 1;
				App->disk->volea_x = App->disk->position.x - 120;
				App->disk->volea_y = App->disk->position.y - (120 / 2.5) - 16;
				if (App->disk->volea_y <= 30) {
					App->disk->disc_speed_X = -2.0;
					App->disk->volea = true;
					App->disk->volea_y = App->disk->position.y;

					App->audio->PlayFx(lobfx, 0);
				}
				else {
					App->disk->disc_speed_X = -2.0;
					App->disk->disc_speed_Y = -1;
					App->disk->volea = true;

					App->audio->PlayFx(lobfx, 0);
				}

			}
		}

		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{

			currentAnimation = &downrightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {


				currentAnimation = &shooting;
				App->disk->currentAnimation2 = &App->disk->moving;

				App->disk->disc_speed_X = -5;
				App->disk->disc_speed_Y = 2;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 2;

			}
			if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)	//volea
			{

				shooting.Reset();
				currentAnimation = &shooting;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 1;
				App->disk->volea_x = App->disk->position.x - 120;
				App->disk->volea_y = App->disk->position.y + (120 / 2.5) + 16;
				if (App->disk->volea_y >= 180) {

					App->disk->disc_speed_X = -2.0;
					App->disk->volea = true;
					App->disk->volea_y = App->disk->position.y;

					App->audio->PlayFx(lobfx, 0);
				}
				else {
					App->disk->disc_speed_X = -2.0;
					App->disk->disc_speed_Y = 1;
					App->disk->volea = true;

					App->audio->PlayFx(lobfx, 0);
				}
			}
		}

		else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			currentAnimation = &downrightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
				currentAnimation = &shooting;
				App->disk->currentAnimation2 = &App->disk->moving;

				App->disk->disc_speed_X=-3;
				App->disk->disc_speed_Y = 6;
				 
				personatgedisc2 = -1;
				App->disk->ultimplayer = 2;/////
			}
			if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)	//volea
			{

				shooting.Reset();
				currentAnimation = &shooting;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 1;
				App->disk->volea_x = App->disk->position.x - 120;
				App->disk->volea_y = App->disk->position.y + (120 / 2.5) + 16;
				if (App->disk->volea_y >= 180) {

					App->disk->disc_speed_X = -2.0;
					App->disk->volea = true;
					App->disk->volea_y = App->disk->position.y;

					App->audio->PlayFx(lobfx, 0);
				}
				else {
					App->disk->disc_speed_X = -2.0;
					App->disk->disc_speed_Y = 1;
					App->disk->volea = true;

					App->audio->PlayFx(lobfx, 0);
				}

			}

		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] != Key_State::KEY_REPEAT)
		{
			shooting.Reset();
			currentAnimation = &shooting;
			App->disk->currentAnimation2 = &App->disk->moving;

			App->disk->disc_speed_X=-6;

			personatgedisc2 = -1;
			App->disk->ultimplayer = 2;/////


		}

		if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN)			//Tirar disc
		{
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE)
			{
				shooting.Reset();
				currentAnimation = &shooting;
				App->disk->currentAnimation2 = &App->disk->moving;
				App->disk->projectile.Reset();


				App->disk->disc_speed_X=-6;
				personatgedisc2 = -1;

				App->disk->ultimplayer = 2;

			}
		}
		if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)	//volea
		{
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_IDLE)
			{
				shooting.Reset();
				currentAnimation = &shooting;
				personatgedisc2 = -1;
				App->disk->volea_x = App->disk->position.x - 120;
				App->disk->volea_y = App->disk->position.y;

				App->disk->ultimplayer = 2;
				App->disk->disc_speed_X = -2.0;
				App->disk->volea = true;

				App->audio->PlayFx(lobfx, 0);
			}
		}
		if (App->player2->ultimate == true) {


			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT) {


				App->disk->ultimate_disk = true;
				App->player2->ultimate = false;

				App->disk->sentido = -1;


				personatgedisc2 = -1;
				App->disk->ultimplayer = 2;

				App->disk->aux2 = App->disk->position.y;
				App->disk->aux = App->disk->position.x;

				App->disk->disc_speed_X = -2;


			}
			else if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {

				/*App->player->currentAnimation = &ultimateanim;*/
				App->disk->ultimate_disk = true;
				App->player2->ultimate = false;


				App->disk->sentido = 1;

				personatgedisc2 = -1;
				App->disk->ultimplayer = 2;

				App->disk->aux2 = App->disk->position.y;
				App->disk->aux = App->disk->position.x;
				App->disk->disc_speed_X = -2;
			}
		}
	}

	

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	/*if (destroyed)		//Estaba a la solucio de la practica 6 nse si farà falta
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}*/

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer2::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x+correcciox, position.y+correccioy, &rect);
	}



	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER2 && c2->type == Collider::Type::BOT_WALL) //collider paret inferior
	{
		position.y = 174;
		
	}
	
	if (c1->type == Collider::Type::PLAYER2 && c2->type == Collider::Type::TOP_WALL) //collider paret superior
	{
		position.y = 29;
		
	}

	if (c1->type == Collider::Type::PLAYER2 && c2->type == Collider::Type::SUPER_ZONE && App->disk->onair == true) {

		if (timer_ult > 0) {
			timer_ult--;

			currentAnimation = &charge_ult;
		}

		if (timer_ult == 0) {
			ultimate = true;

		}
	}
	else if (App->disk->onair == false) {
		timer_ult = 40;
		charge_ult.Reset();
	}


}