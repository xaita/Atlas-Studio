#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 128

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Particle* AddParticle(int xspeed, int yspeed, const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

public:
	//Template particle for an explosion
	Particle explosion;

	//Template particle for a laser
	Particle laser;

	//Template particle for the disk
	Particle disk;
	Particle cargahiromipart;
	Particle klausscanvisentitpart;
	Particle hiromiultipart;
	Particle bhoocargaultipart;
	Particle klausscargaultipart;
	Particle klaussdreta1;
	Particle klaussdreta2;
	Particle klaussdreta3;
	Particle klaussdreta4;
	Particle klaussesquerra1;
	Particle klaussesquerra2;
	Particle klaussesquerra3;
	Particle klaussesquerra4;
	Particle klaussesamunt1;
	Particle klaussesamunt2;
	Particle klaussesamunt3;
	Particle klaussesamunt4;
	Particle klaussesavall1;
	Particle klaussesavall2;
	Particle klaussesavall3;
	Particle klaussesavall4;
	Particle bhootopmurdreta;
	Particle bhootopmuresquerra;
	Particle bhoobotmurdreta;
	Particle bhoobotmuresquerra;
	Particle bhoouppart;
	Particle bhoodownpart;








	

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

};

#endif // !__MODULEPARTICLES_H__