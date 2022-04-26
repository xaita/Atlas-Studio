#include "ModuleDisk.h"

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

ModuleDisk::ModuleDisk(bool startEnabled) : Module(startEnabled)
{
	

	//// animation shoting
	flying.PushBack({ 117, 48, 16, 16 });
	flying.PushBack({ 149, 48, 16, 16 });
	flying.PushBack({ 181, 48, 16, 16 });
	flying.PushBack({ 213, 48, 16, 16 });
	flying.loop = true;
	flying.speed = 0.2f;
	//shooting.loop = false;
	//shooting.pingpong = false;
	//shooting.speed = 0.2f;



}

ModuleDisk::~ModuleDisk()
{

}

bool ModuleDisk::Start()
{
	LOG("Loading disk textures");

	bool ret = true;

	texture = App->textures->Load("Assets\Sprites\Stages\Concrete\Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");
	currentAnimation = &flying;

	/*laserFx = App->audio->LoadFx("Assets/Nau/Fx/laser.wav");*/
	

	position.x = 38;
	position.y = 112;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

Update_Status ModuleDisk::Update()
{
	
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

Update_Status ModuleDisk::PostUpdate()
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

void ModuleDisk::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(0, 0, App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		//App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}