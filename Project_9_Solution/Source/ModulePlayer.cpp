#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleDisk.h"
#include "SDL/include/SDL.h"

#include <chrono>
#include <thread>

#include <stdio.h>

using namespace std::chrono;
using namespace std::this_thread;

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
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
	upAnim.PushBack({ 150, 191, 30, 40 });// frame 1
	upAnim.PushBack({ 120, 191, 30, 51 });// frame 2
	upAnim.PushBack({ 90, 191, 30, 50 });// frame 3
	upAnim.PushBack({ 60, 191, 30, 40 });// frame 4
	upAnim.PushBack({ 30, 191, 30, 53 });// frame 5
	upAnim.PushBack({ 0, 191, 30, 50 });// frame 6
	upAnim.loop = true;
	upAnim.speed = 0.08f;

	// Move down
	downAnim.PushBack({ 240, 148, 29, 43 });// frame 1
	downAnim.PushBack({ 208, 148, 32, 38 });// frame 2
	downAnim.PushBack({ 179, 148, 29, 35 });// frame 3
	downAnim.PushBack({ 155, 148, 24, 41 });// frame 4
	downAnim.PushBack({ 125, 148, 30, 38 });// frame 5
	downAnim.PushBack({ 94, 148, 31, 34 });// frame 6
	downAnim.loop = true;
	downAnim.speed = 0.08f;

	// move right 
	rightAnim.PushBack({ 454, 148, 45, 32 }); // frame 1
	rightAnim.PushBack({ 426, 148, 28, 33 }); // frame 2
	rightAnim.PushBack({ 385, 148, 41, 36 }); // frame 3
	rightAnim.PushBack({ 339, 148, 46, 29 }); // frame 4
	rightAnim.PushBack({ 310, 148, 29, 36 }); // frame 5
	rightAnim.PushBack({ 269, 148, 41, 35 }); // frame 6
	rightAnim.loop = true;
	rightAnim.speed = 0.08f;

	// move left
	leftAnim.PushBack({ 455, 404, 45, 32 });
	leftAnim.PushBack({ 427, 404, 28, 33 });
	leftAnim.PushBack({ 386, 404, 40, 36 });
	leftAnim.PushBack({ 340, 404, 45, 29 });
	leftAnim.PushBack({ 311, 404, 28, 36 });
	leftAnim.PushBack({ 270, 404, 40, 35 });
	leftAnim.loop = true;
	leftAnim.speed = 0.08f;

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
	// animation shooting
	shooting.PushBack({ 73, 46, 34, 40 });// frame 1
	shooting.PushBack({ 37, 46, 36, 38 });// frame 2
	shooting.PushBack({ 0, 46, 37, 40 });// frame 3
	shooting.PushBack({ 459, 0,	33,	41 });// frame 4
	shooting.PushBack({ 432, 0,	27,	46 });// frame 5
	shooting.PushBack({ 409, 0,	23,	43 });// frame 6


	shooting.loop = false;
	shooting.pingpong = false;
	shooting.speed = 0.2f;
	
	
	//Animation idle before shooting
	rightidleFrisbee.PushBack({ 0, 514, 47, 48 });
	rightidleFrisbee.PushBack({ 48, 514, 47, 45 });
	rightidleFrisbee.PushBack({ 96, 514, 47, 48 });
	rightidleFrisbee.PushBack({ 144, 514, 47, 48 });
	rightidleFrisbee.PushBack({ 192, 514, 47, 48 });
	rightidleFrisbee.loop = true;
	rightidleFrisbee.speed = 0.08f;

	uprightidleFrisbee.PushBack({ 367, 520, 45, 42 });
	downrightidleFrisbee.PushBack({ 414, 518, 46, 44 });

	block.PushBack({ 49, 0, 28,	35 });
	block.PushBack({ 25, 0, 24, 35 });
	block.PushBack({ 0, 0,	25,	35 });
	
	block.loop = false;
	block.speed = 0.08f;



	//en les diagonals a la dreta l'animació és la mateixa que moure's cap a dalt o baix.

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Characters/Hiromi Mita/JapaneseSpriteSheedCanviL2.png");
	currentAnimation = &rightidleAnim;


	discFx = App->audio->LoadFx("Assets\Audios\SFX and Voice lines\Frisbee/Toss.wav");

	position.x = 38;
	position.y = 112;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 25, 40 }, Collider::Type::PLAYER, this);


	return ret;
}
int ultimadireccio=2; //1=dreta 2=esquerra
int podermoverse = 0;
int personatgedisc = -1;

Update_Status ModulePlayer::Update()
{
	
	// Moving the player with the camera scroll
	App->player->position.x += 0;

	if (dashtimer == 0) {

		dashup = false;
	}

	if (dashtimer > 0) {
		dashtimer--;
	}

if(personatgedisc == -1)	//MOVIMENT PLAYER
{

	if (App->input->keys[SDL_SCANCODE_C] != Key_State::KEY_REPEAT && dashup == false) {
		dashup = true;

	}
	
	if (App->disk->saque == 0) {


		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && position.x > 6)
		{
			position.x -= speed;
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && dashup == true) {
				dashtimer = 15;

			}
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT && dashup == true)
			{
				position.x -= 3 * speed;

				currentAnimation = &leftdash;
			}

			else if (currentAnimation != &leftAnim) {
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}

			if (currentAnimation != &leftdash) {
				leftdash.Reset();
			}

			ultimadireccio = 1;

		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && position.x < 114)
		{
			position.x += speed;

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && dashup == true) {
				dashtimer = 15;

			}
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT && dashup == true)
			{
				position.x += 3 * speed;

				currentAnimation = &rightdash;
			}

			else if (currentAnimation != &rightAnim) {
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}

			if (currentAnimation != &rightdash) {
				rightdash.Reset();

			}
			ultimadireccio = 2;
		}
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT /*&& position.y < 174*/)		//moviment cap a baix
		{
			position.y += speed;
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && dashup == true) {
				dashtimer = 15;

			}
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT && dashup == true)
			{
				position.y += 3 * speed;

				currentAnimation = &downdash;
			}
			else if (currentAnimation != &downAnim && App->input->keys[SDL_SCANCODE_A] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] != Key_State::KEY_REPEAT)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}

			if (currentAnimation != &downdash) {
				downdash.Reset();
			}

		}
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{

			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;

			}
			ultimadireccio = 2;

		}
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{

			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;

			}
			ultimadireccio = 1;
		}
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT /*&& position.y > 29*/)		//moviment cap amunt
		{
			position.y -= speed;

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && dashup == true) {
				dashtimer = 15;

			}
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT && dashup == true)
			{
				position.y -= 3 * speed;

				currentAnimation = &updash;
			}

			else if (currentAnimation != &upAnim && App->input->keys[SDL_SCANCODE_A] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] != Key_State::KEY_REPEAT)
			{

				upAnim.Reset();
				currentAnimation = &upAnim;
			}

			if (currentAnimation != &updash) {
				updash.Reset();
			}
		}
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT && dashup == true)
			{
				currentAnimation = &rightdash;
			}

			else if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;

			}

			ultimadireccio = 2;
			if (currentAnimation != &rightdash) {
				rightdash.Reset();
			}

		}
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{

			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;

			}
			ultimadireccio = 1;
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && currentAnimation != &shooting) {

			currentAnimation = &rightidleAnim;

		}
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && currentAnimation != &shooting) {

			currentAnimation = &rightidleAnim;
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
			&& ultimadireccio == 2)
		{
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {

				blocktimer = 10;
			}

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT) {

				blockup = true;

				if (currentAnimation != &block) {
					block.Reset();
					currentAnimation = &block;

				}


			}
			


		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
			&& ultimadireccio == 1)
			currentAnimation = &leftidleAnim;
	}
	
	if (App->disk->saque == 1 || App->disk->saque == 2) {
		currentAnimation = &rightidleAnim;
	}

}	

	

	if (personatgedisc == 1) {

		
		currentAnimation = &rightidleFrisbee;
	

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D])
		{

			currentAnimation = &uprightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {


				currentAnimation = &shooting;

				App->disk->disc_speed_X = 5;/////////////////////////////////////////
				App->disk->disc_speed_Y = -2;
				personatgedisc = -1;
				App->disk->ultimplayer = 1;

			}
			if (App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_DOWN) {


				currentAnimation = &shooting;
				App->disk->position.x;
				App->disk->position.y;
				personatgedisc = -1;
				App->disk->ultimplayer = 1;

			}
		}

		else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			currentAnimation = &uprightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {


				currentAnimation = &shooting;

				App->disk->disc_speed_X = 3;
				App->disk->disc_speed_Y = -6;
				personatgedisc = -1;
				App->disk->ultimplayer = 1;

			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimation = &downrightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {
				currentAnimation = &shooting;

				App->disk->disc_speed_X = 5;
				App->disk->disc_speed_Y = 2;

				personatgedisc = -1;
				App->disk->ultimplayer = 1;
			}

		}

		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			currentAnimation = &downrightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {
				currentAnimation = &shooting;

				App->disk->disc_speed_X = 3;
				App->disk->disc_speed_Y = 6;

				personatgedisc = -1;
				App->disk->ultimplayer = 1;
			}

		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_S] != Key_State::KEY_REPEAT)
		{
			shooting.Reset();
			currentAnimation = &shooting;

			App->disk->disc_speed_X = 6;
			

			personatgedisc = -1;
			App->disk->ultimplayer = 1;


		}
		
		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN)
		{
			if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
			{
				shooting.Reset();
				currentAnimation = &shooting;
				
				 App->disk->disc_speed_X = 6;
				 personatgedisc = -1;
				
				 App->disk->ultimplayer = 1;
				

				
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

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	

	// TODO 3: Blit the text of the score in at the bottom of the screen    aixo es del joc de la nau encara xdd
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BOT_WALL)				//collider paret inferior
	{
		App->player->position.y = 174;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TOP_WALL)				//collider paret superior
	{
		App->player->position.y = 29;
	}

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_1)		//collider goal
	{
		scoreplayer1 += 5;

		position.x = 38;
		position.y = 112;
	}
	
	else if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_1)
	{
		scoreplayer1 += 3;

		position.x = 38;
		position.y = 112;
	}
}
