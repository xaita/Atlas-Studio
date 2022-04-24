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
	// idle animation - just one sprite
	idleAnim.PushBack({ 900, 183 , 117, 102 });

	// move upwards
	upAnim.PushBack({ 0, 837, 72, 117 });
	upAnim.PushBack({ 912, 720, 78, 117 });
	upAnim.PushBack({ 831, 720, 81, 117 });
	upAnim.PushBack({ 756, 720, 75, 117 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 869, 87, 81, 96 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// move right
	rightAnim.PushBack({ 432, 607, 75, 108 });
	//rightAnim.PushBack({ 789, 176, 111, 102 });
	rightAnim.PushBack({ 393, 1125, 79, 89 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// move left
	leftAnim.PushBack({ 707, 182, 163, 97 });
	leftAnim.PushBack({ 132, 0, 32, 14 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;



	// move diagonal dalt-esquerra
	upAnim.PushBack({ 0, 837, 72, 117 });
	upAnim.PushBack({ 912, 720, 78, 117 });
	upAnim.PushBack({ 831, 720, 81, 117 });
	upAnim.PushBack({ 756, 720, 75, 117 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// move diagonal abaix-esquerra
	upAnim.PushBack({ 0, 837, 72, 117 });
	upAnim.PushBack({ 912, 720, 78, 117 });
	upAnim.PushBack({ 831, 720, 81, 117 });
	upAnim.PushBack({ 756, 720, 75, 117 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	//en les diagonals a la dreta l'animació és la mateixa que moure's cap a dalt o baix.

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Characters/Beeho Yoo/beehoYooSpriteSheet1.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Nau/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Nau/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

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

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	App->player->position.x += 0;

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
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

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

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