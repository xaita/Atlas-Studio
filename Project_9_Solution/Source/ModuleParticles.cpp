#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	disk.anim.PushBack({ 117, 48, 16, 16 });
	disk.anim.PushBack({ 149, 48, 16, 16 });
	disk.anim.PushBack({ 181, 48, 16, 16 });
	disk.anim.PushBack({ 213, 48, 16, 16 });
	disk.speed.x = 3;
	disk.lifetime = 180;
	disk.anim.speed = 0.2f;


	//disk_Up.anim.PushBack({ 117, 48, 16, 16 });
	//disk_Up.anim.PushBack({ 149, 48, 16, 16 });
	//disk_Up.anim.PushBack({ 181, 48, 16, 16 });
	//disk_Up.anim.PushBack({ 213, 48, 16, 16 });
	//disk_Up.speed.x = 3;
	//disk_Up.speed.y = -3;
	//disk_Up.lifetime = 180;
	//disk_Up.anim.speed = 0.2f;

	//disk_Down.anim.PushBack({ 117, 48, 16, 16 });
	//disk_Down.anim.PushBack({ 149, 48, 16, 16 });
	//disk_Down.anim.PushBack({ 181, 48, 16, 16 });
	//disk_Down.anim.PushBack({ 213, 48, 16, 16 });
	//disk_Down.speed.x = 3;
	//disk_Down.speed.y = +3;
	//disk_Down.lifetime = 180;
	//disk_Down.anim.speed = 0.2f;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(int speedx, int speedy, const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;
			newParticle->speed.x = speedx;
			newParticle->speed.y = speedy;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}