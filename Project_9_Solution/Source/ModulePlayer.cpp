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




	// move diagonal dalt-esquerra
	upleftAnim.PushBack({ 150, 447, 30, 40 });// frame 1
	upleftAnim.PushBack({ 120, 447, 30, 51 });// frame 2
	upleftAnim.PushBack({ 90, 447, 30, 50 });// frame 3
	upleftAnim.PushBack({ 60, 447, 30, 40 });// frame 4
	upleftAnim.PushBack({ 30, 447, 30, 53 });// frame 5
	upleftAnim.PushBack({ 0, 447, 30, 50 });// frame 6
	upleftAnim.loop = true;
	upleftAnim.speed = 0.08f;

	// move diagonal abaix-esquerra
	downleftAnim.PushBack({ 240, 404, 29, 43 });// frame 1
	downleftAnim.PushBack({ 208, 404, 32, 38 });// frame 2
	downleftAnim.PushBack({ 179, 404, 29, 35 });// frame 3
	downleftAnim.PushBack({ 155, 404, 24, 41 });// frame 4
	downleftAnim.PushBack({ 125, 404, 30, 38 });// frame 5
	downleftAnim.PushBack({ 94, 148, 31, 34 });// frame 6
	downleftAnim.loop = true;
	downleftAnim.speed = 0.08f;

	// animation shooting
	shooting.PushBack({ 73, 46, 34, 40 });// frame 1
	shooting.PushBack({ 37, 46, 36, 38 });// frame 2
	shooting.PushBack({ 0, 46, 37, 40 });// frame 3
	shooting.PushBack({ 459, 0,	33,	41 });// frame 4
	shooting.PushBack({ 432, 0,	27,	46 });// frame 5
	shooting.PushBack({ 409, 0,	23,	43 });// frame 6
	shooting.loop = false;
	shooting.speed = 0.13f;
	
	
	//Animation idle before shooting
	rightidleFrisbee.PushBack({ 325, 0, 42, 37 });
	uprightidleFrisbee.PushBack({ 367, 0, 42, 37, });
	downrightidleFrisbee.PushBack({ 283, 0, 42,	39 });

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

	/*laserFx = App->audio->LoadFx("Assets/Nau/Fx/laser.wav");*/
	explosionFx = App->audio->LoadFx("Assets/Nau/Fx/explosion.wav");
	discFx = App->audio->LoadFx("Assets\Audios\SFX and Voice lines\Frisbee/Toss.wav");

	position.x = 38;
	position.y = 112;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 25, 40 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Nau/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}
int ultimadireccio=2; //1=dreta 2=esquerra
int podermoverse = 0;
int personatgedisc = -1;
Update_Status ModulePlayer::Update()
{
	if (App->input->keys[SDL_SCANCODE_X] == Key_State::KEY_UP)
	{
		personatgedisc = personatgedisc * -1 ;
	}
	// Moving the player with the camera scroll
	App->player->position.x += 0;

	

if(personatgedisc == -1)
{

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim && App->input->keys[SDL_SCANCODE_W] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_S] != Key_State::KEY_REPEAT)
		{
			
			currentAnimation = &leftAnim;
			ultimadireccio = 1;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;

		if (currentAnimation != &rightAnim && App->input->keys[SDL_SCANCODE_W] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_S] != Key_State::KEY_REPEAT)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
			ultimadireccio = 2;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim && App->input->keys[SDL_SCANCODE_A] != Key_State::KEY_REPEAT)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
	
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
			ultimadireccio = 2;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		
		if (currentAnimation != &downleftAnim)
		{
			downleftAnim.Reset();
			currentAnimation = &downleftAnim;
			ultimadireccio = 1;
		}
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim && App->input->keys[SDL_SCANCODE_A] != Key_State::KEY_REPEAT)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
			ultimadireccio = 2;
		}
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		
		if (currentAnimation != &upleftAnim)
		{
			upleftAnim.Reset();
			currentAnimation = &upleftAnim;
			ultimadireccio = 1;
		}
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
		&& App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE
		&& ultimadireccio == 2)
		currentAnimation = &rightidleAnim;
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE
		&& ultimadireccio == 1)
		currentAnimation = &leftidleAnim;
}	
	



	//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)			//disparar laser
	//{
	//	Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
	//	newParticle->collider->AddListener(this);
	//	App->audio->PlayFx(discFx);
	//}

				//disparar disc
  
int estatdisc=1; //1 si es té el disc, 0 si el llençes


	if (personatgedisc == 1) {

		if (estatdisc == 1) {
			currentAnimation = &rightidleFrisbee;

			if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
			{

				currentAnimation = &uprightidleFrisbee;

				if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {


					Particle* newParticle = App->particles->AddParticle(15, -15, App->particles->disk, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
					newParticle->collider->AddListener(this);
					App->audio->PlayFx(discFx);



				}




			}

			if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
			{
				currentAnimation = &downrightidleFrisbee;

				if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {

					Particle* newParticle = App->particles->AddParticle(15, 15, App->particles->disk, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
					newParticle->collider->AddListener(this);
					App->audio->PlayFx(discFx);

				}

			}

			if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_S] != Key_State::KEY_REPEAT)
			{

				Particle* newParticle = App->particles->AddParticle(15, 0, App->particles->disk, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
				newParticle->collider->AddListener(this);
				App->audio->PlayFx(discFx);


			}

			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
			{
				if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
					&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
					&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
					&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
				{

					Particle* newParticle = App->particles->AddParticle(15, 0, App->particles->disk, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
					newParticle->collider->AddListener(this);
					App->audio->PlayFx(discFx);




				}

			}
		}
		if (estatdisc == 0) {

			shooting.Reset();
			currentAnimation = &shooting;

		}
		personatgedisc = -1;

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
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}