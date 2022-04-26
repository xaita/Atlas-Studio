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

	texture = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");


	position.x = 30;
	position.y = 200;


	destroyed = false;

	diskcollider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::DISK, this);

	return ret;
}

Update_Status ModuleDisk::Update()
{
	

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
	if (c1 == diskcollider && destroyed == false)
	{
		saque = 0;

	}
}