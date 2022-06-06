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
	texture = App->textures->Load("Assets/Sprites/particlesAndEffects.png");
	cargahiromipart.anim.PushBack({ 195, 718, 65, 65 });
	cargahiromipart.anim.PushBack({ 130, 718, 65, 65 });
	cargahiromipart.anim.PushBack({ 65, 718, 65, 65 });
	cargahiromipart.anim.PushBack({ 0, 718, 65, 65 });
	cargahiromipart.anim.PushBack({ 195, 653, 65, 65 });
	cargahiromipart.anim.PushBack({ 130, 653, 65, 65 });
	cargahiromipart.anim.PushBack({ 65, 653, 65, 65 });
	cargahiromipart.anim.PushBack({ 0, 653, 65, 65 });
	cargahiromipart.anim.PushBack({ 195, 588, 65, 65 });
	cargahiromipart.anim.PushBack({ 130, 588, 65, 65 });
	cargahiromipart.anim.PushBack({ 65, 588, 65, 65 });
	cargahiromipart.anim.PushBack({ 0, 588, 65, 65 });
	cargahiromipart.anim.PushBack({ 195, 523, 65, 65 });
	cargahiromipart.anim.PushBack({ 130, 523, 65, 65 });
	cargahiromipart.anim.PushBack({ 65, 523, 65, 65 });
	cargahiromipart.anim.PushBack({ 0, 523, 65, 65 });

	cargahiromipart.lifetime = 40;
	cargahiromipart.anim.pingpong = false;
	cargahiromipart.anim.loop = false;
	cargahiromipart.anim.speed = 0.7f;


	klausscanvisentitpart.anim.PushBack({ 1, 342, 53, 51 });
	klausscanvisentitpart.anim.PushBack({ 54, 342, 53, 51 });
	klausscanvisentitpart.anim.PushBack({ 107, 342, 53, 51 });
	klausscanvisentitpart.anim.PushBack({ 160, 342, 53, 51 });
	klausscanvisentitpart.anim.PushBack({ 212, 342, 53, 51 });
	klausscanvisentitpart.anim.PushBack({ 266, 342, 53, 51 });
	klausscanvisentitpart.anim.PushBack({ 319, 342, 53, 51 });
	klausscanvisentitpart.lifetime = 20;
	klausscanvisentitpart.anim.speed = 0.1f;

	hiromiultipart.anim.PushBack({ 203, 114, 14, 96 });
	hiromiultipart.anim.PushBack({ 218, 114, 16, 96 });
	hiromiultipart.anim.PushBack({ 235, 114, 16, 96 });
	hiromiultipart.anim.PushBack({ 252, 114, 16, 96 });
	hiromiultipart.anim.PushBack({ 269, 114, 16, 96 });
	hiromiultipart.anim.PushBack({ 286, 114, 16, 96 });
	hiromiultipart.anim.PushBack({ 303, 114, 16, 96 });
	hiromiultipart.lifetime = 15;
	hiromiultipart.anim.speed = 0.3f;

	bhoocargaultipart.anim.PushBack({ 207, 58, 50, 53 });
	bhoocargaultipart.anim.PushBack({ 267, 59, 50, 53 });
	bhoocargaultipart.anim.PushBack({ 327, 61, 50, 53 });
	bhoocargaultipart.anim.PushBack({ 388, 60, 50, 53 });
	bhoocargaultipart.lifetime = 20;
	bhoocargaultipart.anim.speed = 0.1f;

	klausscargaultipart.anim.PushBack({ 408, 139, 50, 50 });
	klausscargaultipart.anim.PushBack({ 408, 187, 50, 50 });
	klausscargaultipart.anim.PushBack({ 456, 139, 50, 50 });
	klausscargaultipart.anim.PushBack({ 456, 187, 50, 50 });
	klausscargaultipart.lifetime = 20;
	klausscargaultipart.anim.speed = 0.1f;


	klaussdreta1.anim.PushBack({ 203, 438, 23, 32 });
	klaussdreta1.lifetime = 10;
	klaussdreta2.anim.PushBack({ 256, 438, 33, 32 });
	klaussdreta2.lifetime = 10;
	klaussdreta3.anim.PushBack({ 299, 438, 47, 31 });
	klaussdreta3.lifetime = 10;
	klaussdreta4.anim.PushBack({ 354, 438, 58, 32 });
	klaussdreta4.lifetime = 10;

	klaussesquerra1.anim.PushBack({ 389, 473, 23, 32 });
	klaussesquerra1.lifetime = 10;
	klaussesquerra2.anim.PushBack({ 326, 473, 33, 32 });
	klaussesquerra2.lifetime = 10;
	klaussesquerra3.anim.PushBack({ 269, 473, 47, 31 });
	klaussesquerra3.lifetime = 10;
	klaussesquerra4.anim.PushBack({ 203, 473, 58, 32 });
	klaussesquerra4.lifetime = 10;

	klaussesamunt1.anim.PushBack({ 437, 482, 32, 23 });
	klaussesamunt1.lifetime = 10;
	klaussesamunt2.anim.PushBack({ 437, 419, 32, 33 });
	klaussesamunt2.lifetime = 10;
	klaussesamunt3.anim.PushBack({ 437, 362, 31, 47 });
	klaussesamunt3.lifetime = 10;
	klaussesamunt4.anim.PushBack({ 437, 296, 32, 58 });
	klaussesamunt4.lifetime = 10;

	klaussesavall1.anim.PushBack({ 473, 269, 32, 23 });
	klaussesavall1.lifetime = 10;
	klaussesavall2.anim.PushBack({ 473, 349, 33, 32 });
	klaussesavall2.lifetime = 10;
	klaussesavall3.anim.PushBack({ 473, 392, 31, 47 });
	klaussesavall3.lifetime = 10;
	klaussesavall4.anim.PushBack({ 473, 447, 32, 58 });
	klaussesavall4.lifetime = 10;

	bhootopmurdreta.anim.PushBack({ 4, 254, 32, 19 });
	bhootopmurdreta.anim.PushBack({ 37, 254, 32, 19 });
	bhootopmurdreta.anim.PushBack({ 70, 254, 32, 19 });
	bhootopmurdreta.anim.PushBack({ 101, 254, 32, 19 });
	bhootopmurdreta.lifetime = 20;
	bhootopmurdreta.anim.speed = 0.1f;

	bhootopmuresquerra.anim.PushBack({ 133, 283, 30, 19 });
	bhootopmuresquerra.anim.PushBack({ 99, 283, 30, 19 });
	bhootopmuresquerra.anim.PushBack({ 65, 283, 30, 19 });
	bhootopmuresquerra.anim.PushBack({ 34, 283, 30, 19 });
	bhootopmuresquerra.lifetime = 20;
	bhootopmuresquerra.anim.speed = 0.1f;

	bhoobotmurdreta.anim.PushBack({ 4, 214, 32, 19 });
	bhoobotmurdreta.anim.PushBack({ 37, 214, 32, 19 });
	bhoobotmurdreta.anim.PushBack({ 70, 214, 32, 19 });
	bhoobotmurdreta.anim.PushBack({ 101, 214, 32, 19 });
	bhoobotmurdreta.lifetime = 20;
	bhoobotmurdreta.anim.speed = 0.1f;

	bhoobotmuresquerra.anim.PushBack({ 133, 315, 30, 19 });
	bhoobotmuresquerra.anim.PushBack({ 99, 315, 30, 19 });
	bhoobotmuresquerra.anim.PushBack({ 65, 315, 30, 19 });
	bhoobotmuresquerra.anim.PushBack({ 34, 315, 30, 19 });
	bhoobotmuresquerra.lifetime = 20;
	bhoobotmuresquerra.anim.speed = 0.1f;

	bhoouppart.anim.PushBack({ 274, 274, 16, 14 });
	bhoouppart.anim.PushBack({ 274, 265, 16, 16 });
	bhoouppart.anim.PushBack({ 274, 237, 16, 15 });
	bhoouppart.anim.PushBack({ 274, 220, 16, 13 });
	bhoouppart.lifetime = 20;
	bhoouppart.anim.speed = 0.1f;

	bhoodownpart.anim.PushBack({ 293,  220, 16, 14 });
	bhoodownpart.anim.PushBack({ 293,  236, 16, 16 });
	bhoodownpart.anim.PushBack({ 293,  256, 16, 15 });
	bhoodownpart.anim.PushBack({ 293, 275, 16, 13 });
	bhoodownpart.lifetime = 20;
	bhoodownpart.anim.speed = 0.1f;

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