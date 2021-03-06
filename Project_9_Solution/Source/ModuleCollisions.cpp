#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;



	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DISK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SUPER_ZONE] = true;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::PLAYER2][Collider::Type::PLAYER2] = false;
	matrix[Collider::Type::PLAYER2][Collider::Type::DISK] = true;
	matrix[Collider::Type::PLAYER2][Collider::Type::SUPER_ZONE] = true;

	matrix[Collider::Type::OBSTACLE1][Collider::Type::DISK] = true;
	matrix[Collider::Type::OBSTACLE1][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::OBSTACLE1][Collider::Type::PLAYER2] = false;

	matrix[Collider::Type::DISK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DISK][Collider::Type::PLAYER2] = true;
	matrix[Collider::Type::DISK][Collider::Type::SCOREZONE_1] = true;
	matrix[Collider::Type::DISK][Collider::Type::SCOREZONE_2] = true;
	matrix[Collider::Type::DISK][Collider::Type::TOP_WALL] = true;
	matrix[Collider::Type::DISK][Collider::Type::BOT_WALL] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::TOP_WALL] = true;
	matrix[Collider::Type::PLAYER2][Collider::Type::TOP_WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOT_WALL] = true;
	matrix[Collider::Type::PLAYER2][Collider::Type::BOT_WALL] = true;


	matrix[Collider::Type::SCOREZONE_1][Collider::Type::DISK] = true;
	matrix[Collider::Type::SCOREZONE_2][Collider::Type::DISK] = true;

	matrix[Collider::Type::TOP_WALL][Collider::Type::DISK] = true;
	matrix[Collider::Type::TOP_WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TOP_WALL][Collider::Type::PLAYER2] = true;
	matrix[Collider::Type::BOT_WALL][Collider::Type::DISK] = true;
	matrix[Collider::Type::TOP_WALL][Collider::Type::PLAYER2] = true;
	matrix[Collider::Type::TOP_WALL][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::SUPER_ZONE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SUPER_ZONE][Collider::Type::PLAYER2] = true;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::PLAYER2: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::DISK: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::SCOREZONE_2: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::SCOREZONE_1: // nega
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
			case Collider::Type::BOT_WALL:		//yellow
			App->render->DrawQuad(colliders[i]->rect, 100, 0, 0, alpha);
			break;		
			case Collider::Type::TOP_WALL:		//yellow
			App->render->DrawQuad(colliders[i]->rect, 100, 0, 0, alpha);
			break;
			case Collider::Type::OBSTACLE1: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 250, 126, alpha);
				break;
			case Collider::Type:: SUPER_ZONE:
				App->render->DrawQuad(colliders[i]->rect, 163, 73, 164, alpha);
				break;

		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}