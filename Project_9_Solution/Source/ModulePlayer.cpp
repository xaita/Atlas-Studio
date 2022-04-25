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

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
<<<<<<< Updated upstream
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
	rightidleAnim.speed = 0.12f;
=======
	// idle animation
	idleAnim.PushBack({ 393, 103 , 23, 36 });// frame 1
	idleAnim.PushBack({ 370, 103 , 23, 35 });// frame 2
	idleAnim.PushBack({ 347, 103 , 23, 36 });// frame 3
	idleAnim.PushBack({ 323, 103 , 24, 36 });// frame 4
	idleAnim.PushBack({ 299, 103 , 24, 35 });// frame 5
	idleAnim.PushBack({ 275, 103 , 24, 36 });// frame 6
	idleAnim.PushBack({ 251, 103 , 24, 39 });// frame 7
	idleAnim.PushBack({ 227, 103 , 24, 37 });// frame 8
	idleAnim.loop = true;
	idleAnim.speed = 0.12f;
>>>>>>> Stashed changes

	// idle left animation
	idleLeftAnim.PushBack({ 393, 359 , 23, 36 });// frame 1
	idleLeftAnim.PushBack({ 370, 359 , 23, 35 });// frame 2
	idleLeftAnim.PushBack({ 347, 359 , 23, 36 });// frame 3
	idleLeftAnim.PushBack({ 323, 359 , 24, 36 });// frame 4
	idleLeftAnim.PushBack({ 299, 359 , 24, 35 });// frame 5
	idleLeftAnim.PushBack({ 275, 359 , 24, 36 });// frame 6
	idleLeftAnim.PushBack({ 251, 359 , 24, 39 });// frame 7
	idleLeftAnim.PushBack({ 227, 359 , 24, 37 });// frame 8
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.12f;

	leftidleAnim.PushBack({ 393, 359 , 23, 36 });// frame 1
	leftidleAnim.PushBack({ 370, 359 , 23, 35 });// frame 2
	leftidleAnim.PushBack({ 347, 359 , 23, 36 });// frame 3
	leftidleAnim.PushBack({ 323, 359 , 24, 36 });// frame 4
	leftidleAnim.PushBack({ 299, 359 , 24, 35 });// frame 5
	leftidleAnim.PushBack({ 275, 359 , 24, 36 });// frame 6
	leftidleAnim.PushBack({ 251, 359 , 24, 39 });// frame 7
	leftidleAnim.PushBack({ 227, 359 , 24, 37 });// frame 8
	leftidleAnim.loop = true;
	leftidleAnim.speed = 0.12f;

	// move upwards
	upAnim.PushBack({ 150, 191, 30, 40 });// frame 1
	upAnim.PushBack({ 120, 191, 30, 51 });// frame 2
	upAnim.PushBack({ 90, 191, 30, 50 });// frame 3
	upAnim.PushBack({ 60, 191, 30, 40 });// frame 4
	upAnim.PushBack({ 30, 191, 30, 53 });// frame 5
	upAnim.PushBack({ 0, 191, 30, 50 });// frame 6
	upAnim.loop = true;
	upAnim.speed = 0.15f;

	// Move down
	downAnim.PushBack({ 240, 148, 29, 43 });// frame 1
	downAnim.PushBack({ 208, 148, 32, 38 });// frame 2
	downAnim.PushBack({ 179, 148, 29, 35 });// frame 3
	downAnim.PushBack({ 155, 148, 24, 41 });// frame 4
	downAnim.PushBack({ 125, 148, 30, 38 });// frame 5
	downAnim.PushBack({ 94, 148, 31, 34 });// frame 6
	downAnim.loop = true;
	downAnim.speed = 0.15f;

	// move right 
	rightAnim.PushBack({ 454, 148, 45, 32 }); // frame 1
	rightAnim.PushBack({ 426, 148, 28, 33 }); // frame 2
	rightAnim.PushBack({ 385, 148, 41, 36 }); // frame 3
	rightAnim.PushBack({ 339, 148, 46, 29 }); // frame 4
	rightAnim.PushBack({ 310, 148, 29, 36 }); // frame 5
	rightAnim.PushBack({ 269, 148, 41, 35 }); // frame 6
	rightAnim.loop = true;
	rightAnim.speed = 0.17f;

	// move left
	leftAnim.PushBack({ 455, 404, 45, 32 });
	leftAnim.PushBack({ 427, 404, 28, 33 });
	leftAnim.PushBack({ 386, 404, 40, 36 });
	leftAnim.PushBack({ 340, 404, 45, 29 });
	leftAnim.PushBack({ 311, 404, 28, 36 });
	leftAnim.PushBack({ 270, 404, 40, 35 });
	leftAnim.loop = true;
	leftAnim.speed = 0.17f;




	// move diagonal dalt-esquerra
	upleftAnim.PushBack({ 0, 837, 72, 117 });
	upleftAnim.PushBack({ 912, 720, 78, 117 });
	upleftAnim.PushBack({ 831, 720, 81, 117 });
	upleftAnim.PushBack({ 756, 720, 75, 117 });
	upleftAnim.loop = true;
	upleftAnim.speed = 0.1f;

	// move diagonal abaix-esquerra
	downleftAnim.PushBack({ 240, 404, 29, 43 });// frame 1
	downleftAnim.PushBack({ 208, 404, 32, 38 });// frame 2
	downleftAnim.PushBack({ 179, 404, 29, 35 });// frame 3
	downleftAnim.PushBack({ 155, 404, 24, 41 });// frame 4
	downleftAnim.PushBack({ 125, 404, 30, 38 });// frame 5
	downleftAnim.PushBack({ 94, 404, 31, 34 });// frame 6
	downleftAnim.loop = true;
	downleftAnim.speed = 0.1f;

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

	laserFx = App->audio->LoadFx("Assets/Nau/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Nau/Fx/explosion.wav");

	position.x = 38;
	position.y = 112;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 117, 102 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Nau/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}
int a=0;
Update_Status ModulePlayer::Update()
{
	
	// Moving the player with the camera scroll
	App->player->position.x += 0;
	
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim && App->input->keys[SDL_SCANCODE_W] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_S] != Key_State::KEY_REPEAT)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
			a = 1;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;

		if (currentAnimation != &rightAnim && App->input->keys[SDL_SCANCODE_W] != Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_S] != Key_State::KEY_REPEAT)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
			a = 2;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
	
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
			a = 2;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		
		if (currentAnimation != &downleftAnim)
		{
			downleftAnim.Reset();
			currentAnimation = &downleftAnim;
			a = 1;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
			a = 2;
		}
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		
		if (currentAnimation != &upleftAnim)
		{
			upAnim.Reset();
			currentAnimation = &upleftAnim;
			a = 1;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
	



	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)			//disparar laser
	{
		Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		newParticle->collider->AddListener(this);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)			//disparar disc
	{
		Particle* newParticle = App->particles->AddParticle(App->particles->disk, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		newParticle->collider->AddListener(this);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE					//idle dreta
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
<<<<<<< Updated upstream
<<<<<<< Updated upstream
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		currentAnimation = &rightidleAnim;
=======
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_UP)
		currentAnimation = &idleAnim;
>>>>>>> Stashed changes

	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE					//idle esquerra
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_UP
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		currentAnimation = &idleLeftAnim;
=======
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE && a == 2)
		currentAnimation = &rightidleAnim;
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE && a == 1)
		currentAnimation = &leftidleAnim;
>>>>>>> Stashed changes

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
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}