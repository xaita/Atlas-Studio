#include "ModuleDisk.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "SDL/include/SDL.h"

ModuleDisk::ModuleDisk(bool startEnabled) : Module(startEnabled)
{
	// moving animation
	moving.PushBack({ 117, 48, 16, 16 });
	moving.PushBack({ 149, 48, 16, 16 });
	moving.PushBack({ 181, 48, 16, 16 });
	moving.PushBack({ 213, 48, 16, 16 });
	moving.loop = true;
	moving.speed = 0.1f;

	// Projectile motion animation
	projectile.PushBack({ 35, 8, 32, 14 });
	projectile.PushBack({ 53, 7, 25, 31 });
	projectile.PushBack({ 79, 6, 36, 34 });
	projectile.PushBack({ 116, 5, 28, 36 });
	projectile.PushBack({ 145, 4, 21, 38 });
	projectile.PushBack({ 167, 3, 3, 39 });
	projectile.PushBack({ 171, 2, 23, 41 });
	projectile.PushBack({ 195, 2, 33, 42 });
	projectile.PushBack({ 229, 0, 43, 44 });
	projectile.loop = false;
	projectile.speed = 0.1f;

}

ModuleDisk::~ModuleDisk()
{

}

bool ModuleDisk::Start()
{
	currentAnimation2 = &moving;
	LOG("Loading Disk textures");

	bool ret = true;
	timer = 120;

	texture = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");


	position.x = 145; //Posicio arbitre
	position.y = 191; //posicio arbitre


	destroyed = false;

	diskcollider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::DISK, this);

	return ret;
}

Update_Status ModuleDisk::Update()
{
	if (saque == 1) {
		timer -= 1;
		App->player->position.x = 38;
		App->player->position.y = 112;

		App->player2->position.x = 240;
		App->player2->position.y = 112;
    }
	
	if (saque == 1  && timer ==0) {

		

		disc_speed_X = -3;
		disc_speed_Y = -2;



	}

	if (saque == 0 && position.y >= 180) {

		disc_speed_Y = -disc_speed_Y;
		

	}

	if (saque == 0 && position.y <=30) {

		disc_speed_Y = -disc_speed_Y;

	}

	

	
	position.x += disc_speed_X;
	position.y += disc_speed_Y;

	diskcollider->SetPos(position.x, position.y);



	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleDisk::PostUpdate()
{
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y, &rect2);
	return Update_Status::UPDATE_CONTINUE;
}

void ModuleDisk::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER)
	{
	    App->player->personatgedisc = 1;


		position.x = App->player->position.x + 40;

		position.y = App->player->position.y + 10;

		disc_speed_X = 0;
		disc_speed_Y = 0;

		saque = 0;


	}


	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER2)
	{
		App->player2->personatgedisc2 = 1;


		position.x = App->player2->position.x -20;

		position.y = App->player2->position.y + 10;

		disc_speed_X = 0;
		disc_speed_Y = 0;
		saque = 0;

	}
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_1)
	{
		
		position.x = 143;
		position.y = 191;
		disc_speed_X = 0;
		disc_speed_Y = 0;

		timer = 120;

		saque = 1;
		


	}
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_2)
	{
		
		position.x = 143;
		position.y = 191;
		disc_speed_X = 0;
		disc_speed_Y = 0;

		timer = 120;

		saque = 1;
		

	}
	
	



}