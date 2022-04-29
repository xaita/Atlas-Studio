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

#include <chrono>
#include <thread>

#include <stdio.h>

using namespace std::chrono;
using namespace std::this_thread;

ModulePlayer2::ModulePlayer2(bool startEnabled) : Module(startEnabled)
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
	upAnim.PushBack({ 150, 447, 30, 40 });// frame 1
	upAnim.PushBack({ 120, 447, 30, 51 });// frame 2
	upAnim.PushBack({ 90, 447, 30, 50 });// frame 3
	upAnim.PushBack({ 60, 447, 30, 40 });// frame 4
	upAnim.PushBack({ 30, 447, 30, 53 });// frame 5
	upAnim.PushBack({ 0, 447, 30, 50 });// frame 6
	upAnim.loop = true;
	upAnim.speed = 0.08f;

	// Move down
	downAnim.PushBack({ 240, 404, 29, 43 });// frame 1
	downAnim.PushBack({ 208, 404, 32, 38 });// frame 2
	downAnim.PushBack({ 179, 404, 29, 35 });// frame 3
	downAnim.PushBack({ 155, 404, 24, 41 });// frame 4
	downAnim.PushBack({ 125, 404, 30, 38 });// frame 5
	downAnim.PushBack({ 94, 404, 31, 34 });// frame 6
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
	

	//en les diagonals a la dreta l'animació és la mateixa que moure's cap a dalt o baix.

}

ModulePlayer2::~ModulePlayer2()
{

}

bool ModulePlayer2::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Characters/Hiromi Mita/JapaneseSpriteSheedCanviL2P2.png");
	currentAnimation = &leftidleAnim;

	/*laserFx = App->audio->LoadFx("Assets/Nau/Fx/laser.wav");*/
	explosionFx = App->audio->LoadFx("Assets/Nau/Fx/explosion.wav");
	discFx = App->audio->LoadFx("Assets\Audios\SFX and Voice lines\Frisbee/Toss.wav");

	position.x = 240;
	position.y = 112;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 25, 40 }, Collider::Type::PLAYER2, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Nau/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}
int ultimadireccio2 = 1; //1=esquerra 2=dreta
int podermoverse2 = 0;

Update_Status ModulePlayer2::Update()
{

	// Moving the player with the camera scroll
	App->player2->position.x += 0;



	if (personatgedisc2 == -1)
	{
		if (App->disk->saque == 0) {
			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && position.x > 162)
			{
				position.x -= speed;
				if (currentAnimation != &leftAnim && App->input->keys[SDL_SCANCODE_UP] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] != Key_State::KEY_REPEAT)
				{

					currentAnimation = &leftAnim;
					ultimadireccio2 = 1;
				}
			}

			if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && position.x < 274)
			{
				position.x += speed;

				if (currentAnimation != &rightAnim && App->input->keys[SDL_SCANCODE_UP] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] != Key_State::KEY_REPEAT)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					ultimadireccio2 = 2;
				}
			}
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && position.y < 174)
			{
				position.y += speed;
				if (currentAnimation != &downAnim && App->input->keys[SDL_SCANCODE_LEFT] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] != Key_State::KEY_REPEAT)
				{
					downAnim.Reset();
					currentAnimation = &downAnim;
				}
			}
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
			{

				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					ultimadireccio2 = 2;
				}
			}
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
			{

				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
					ultimadireccio2 = 1;
				}
			}
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && position.y > 29)
			{
				position.y -= speed;
				if (currentAnimation != &upAnim && App->input->keys[SDL_SCANCODE_LEFT] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] != Key_State::KEY_REPEAT)
				{
					upAnim.Reset();
					currentAnimation = &upAnim;
				}
			}
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
			{

				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					ultimadireccio2 = 2;
				}
			}
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
			{

				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
					ultimadireccio2 = 1;
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
				currentAnimation = &rightidleAnim;
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_IDLE
				&& ultimadireccio2 == 1)
				currentAnimation = &leftidleAnim;
		}

		if (App->disk->saque == 2 || App->disk->saque == 1) {

			currentAnimation = &leftidleAnim;

		}

	}






	if (personatgedisc2 == 1) {


		currentAnimation = &rightidleFrisbee;

		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{

			currentAnimation = &uprightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {


				currentAnimation = &shooting;

				App->disk->disc_speed_X = -5;
				App->disk->disc_speed_Y = -2;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 1;

			}
		}

		else if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{

			currentAnimation = &uprightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {

				currentAnimation = &shooting;

				App->disk->disc_speed_X=-3;
				App->disk->disc_speed_Y = -6;

				personatgedisc2 = -1;

				App->disk->ultimplayer = 1;/////
			}
		}

		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{

			currentAnimation = &downrightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {


				currentAnimation = &shooting;

				App->disk->disc_speed_X = -5;
				App->disk->disc_speed_Y = 2;
				personatgedisc2 = -1;
				App->disk->ultimplayer = 1;

			}
		}

		else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			currentAnimation = &downrightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
				currentAnimation = &shooting;

				App->disk->disc_speed_X=-3;
				App->disk->disc_speed_Y = 6;
				 
				personatgedisc2 = -1;
				App->disk->ultimplayer = 1;/////
			}

		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] != Key_State::KEY_REPEAT)
		{
			shooting.Reset();
			currentAnimation = &shooting;

			App->disk->disc_speed_X=-6;

			personatgedisc2 = -1;
			App->disk->ultimplayer = 1;/////


		}

		if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN)
		{
			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE)
			{
				shooting.Reset();
				currentAnimation = &shooting;

				App->disk->disc_speed_X=-6;
				personatgedisc2 = -1;

				App->disk->ultimplayer = 2;



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
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------


	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{


	if (c1->type == Collider::Type::PLAYER2 && c2->type == Collider::Type::DISK)
	{
		personatgedisc2=1;
	}
}