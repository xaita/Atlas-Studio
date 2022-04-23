#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 900, 183 , 117, 102 });

	// move upwards
	upAnim.PushBack({ 0, 837, 72, 117 });
	upAnim.PushBack({ 912, 720, 78, 117 });
	upAnim.PushBack({ 831, 720, 81, 117 });
	upAnim.PushBack({ 756, 720, 75, 117 });
	upAnim.loop = true;
	upAnim.speed = 0.1;

	// Move down
	downAnim.PushBack({ 869, 87, 81, 96 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = true;
	downAnim.speed = 0.1;

	// move right
	rightAnim.PushBack({ 432, 607, 75, 108 });
	//rightAnim.PushBack({ 789, 176, 111, 102 });
	rightAnim.PushBack({ 393, 1125, 79, 89 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1;

	// move left
	leftAnim.PushBack({ 707, 182, 163, 97 });
	leftAnim.PushBack({ 132, 0, 32, 14 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1;



	// move diagonal dalt-esquerra
	upAnim.PushBack({ 0, 837, 72, 117 });
	upAnim.PushBack({ 912, 720, 78, 117 });
	upAnim.PushBack({ 831, 720, 81, 117 });
	upAnim.PushBack({ 756, 720, 75, 117 });
	upAnim.loop = true;
	upAnim.speed = 0.1;

	// move diagonal abaix-esquerra
	upAnim.PushBack({ 0, 837, 72, 117 });
	upAnim.PushBack({ 912, 720, 78, 117 });
	upAnim.PushBack({ 831, 720, 81, 117 });
	upAnim.PushBack({ 756, 720, 75, 117 });
	upAnim.loop = true;
	upAnim.speed = 0.1;

	//en les diagonals a la dreta l'animació és la mateixa que moure's cap a dalt o baix.
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Characters/Beeho Yoo/beehoYooSpriteSheet1.png"); // arcade version
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 150;
	position.y = 120;

	// TODO 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 117, 102 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	App->player->position.x += 0;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}

	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;
		// TODO 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}


update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Detect collision with a wall. If so, go back to intro screen.
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
}