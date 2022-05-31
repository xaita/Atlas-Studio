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
#include"SceneLevel1.h"
#include"SceneIntroSNK.h"
#include "Animation.h"
#include "SDL/include/SDL.h"
#include "PropsBackground.h"

ModuleDisk::ModuleDisk(bool startEnabled) : Module(startEnabled)
{
	// moving animation
	moving.PushBack({ 117, 48, 16, 16 });
	moving.PushBack({ 149, 48, 16, 16 });
	moving.PushBack({ 181, 48, 16, 16 });
	moving.PushBack({ 213, 48, 16, 16 });
	moving.loop = true;
	moving.speed = 0.2f;

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

	invisible.PushBack({ 0,0,0,0 });

	blocking.PushBack({ 17, 29, 35, 8 });

}

ModuleDisk::~ModuleDisk()
{

}

bool ModuleDisk::Start()
{
	App->collisions->Enable();
	currentAnimation2 = &moving;
	LOG("Loading Disk textures");

	si = 0;
	bool ret = true;
	muerte_subita = false;
	timer = 120;
	timer_Win = 300;

	texture = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");


	position.x = 145; //Posicio arbitre
	position.y = 191; //posicio arbitre


	destroyed = false;

	diskcollider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::DISK, this);

	return ret;
}

Update_Status ModuleDisk::Update()
{
	if (App->sceneLevel_1->timer2 == 0) {

		if (score_player_1 > score_player_2) {

			sets_player1 +=1;
			saque = 2;
			sets += 1;
			timer_set = 300;
			score_player_1 = 0;
			score_player_2 = 0;
			App->player->personatgedisc = -1;
			App->player2->personatgedisc2 = -1;
			position.x = 143;
			position.y = 191;
			App->sceneLevel_1->timer2 = 1800;
			App->sceneLevel_1->timer.Reset();
			App->propsBackground->timersetcount = 350;
		}

		else if (score_player_2 > score_player_1) {

			sets_player2 +=1;
			saque = 1;
			sets += 1;
			timer_set = 300;
			score_player_1 = 0;
			score_player_2 = 0;
			App->player->personatgedisc = -1;
			App->player2->personatgedisc2 = -1;
			position.x = 143;
			position.y = 191;
			App->sceneLevel_1->timer2 = 1800;
			App->sceneLevel_1->timer.Reset();
			App->propsBackground->timersetcount = 350;
		}

		else if (score_player_1 == score_player_2) {


			sets_player1 += 1;
			sets_player2 += 1;
			if (sets_player1 == 2 && sets_player2 == 2) {

				muerte_subita = true;
				saque = 1;
				sets += 1;
				timer_set = 300;
				score_player_1 = 0;
				score_player_2 = 0;
				App->player->personatgedisc = -1;
				App->player2->personatgedisc2 = -1;
				position.x = 143;
				position.y = 191;
				App->sceneLevel_1->timer2 = 1800;
				App->sceneLevel_1->timer.Reset();
				App->propsBackground->timersetcount = 350;

			}
			else {

				saque = 1;
				sets += 1;
				timer_set = 300;
				score_player_1 = 0;
				score_player_2 = 0;
				App->player->personatgedisc = -1;
				App->player2->personatgedisc2 = -1;
				position.x = 143;
				position.y = 191;
				App->sceneLevel_1->timer2 = 1800;
				App->sceneLevel_1->timer.Reset();
				App->propsBackground->timersetcount = 350;
			}
		

		}

	}
	if (App->player->personatgedisc == -1 && App->player2->personatgedisc2 == -1) {
		currentAnimation2 = &moving;
	}

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {
		godmode *= -1;
	}


	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) {
		sets_player1 = 2;
	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
		sets_player2 = 2;
	}

	if ((sets_player1== 2 || sets_player2==2) && si ==1 && muerte_subita ==false) {
		
		timer_Win -= 1;
		
	
		if (timer_Win <= 0) {

			sets_player1 = 0;
			sets_player2 = 0;

			saque = 1;

			App->sceneLevel_1->Disable();

			App->sceneIntroSNK->Enable();

			App->collisions->Disable();
		

		}
	}
	


	if (score_player_1 >= 12) {

		sets_player1 += 1;
		sets += 1;
		saque = 2;
		timer_set = 300;
		score_player_1 = 0;
		score_player_2 = 0;
		App->sceneLevel_1->timer2 = 1800;
		App->sceneLevel_1->timer.Reset();
	}

	if (score_player_2 >= 12) {

		sets_player2 += 1;
		sets += 1;
	
		App->sceneLevel_1->timer2 = 1800;
		saque = 1;

		timer_set = 300;
		score_player_1 = 0;
		score_player_2 = 0;
		App->player->currentAnimation= &App->player->rightidleAnim;
		App->player2->currentAnimation = &App->player2->leftidleAnim;
		App->sceneLevel_1->timer.Reset();
	}

	if (saque == 1 || saque ==2) {
		if (timer > 0) {
			timer -= 1;
		}
		timer_set -= 1;
		App->player->position.x = 38;
		App->player->position.y = 112;

		App->player2->position.x = 240;
		App->player2->position.y = 112;
    }
	
	if (saque == 1  && timer ==0 && timer_set <= 0 ) {

		

		disc_speed_X = -3;
		disc_speed_Y = -2;



	}

	if (saque == 2 && timer == 0 && timer_set <= 0) {



		disc_speed_X = 3;
		disc_speed_Y = -2;



	}

	if (saque == 0 && position.y >= 180) {

		disc_speed_Y = -disc_speed_Y;
		

	}

	if (saque == 0 && position.y <=30) {

		disc_speed_Y = -disc_speed_Y;

	}

	--timerblock;

	
	if (bloqueig == true) {
		currentAnimation2 = &blocking;
		timerblock = 600;
		bloqueig == false;
	}
	


	
	position.x += disc_speed_X;
	position.y += disc_speed_Y;

	diskcollider->SetPos(position.x, position.y);
	currentAnimation2->Update();

	App->propsBackground->timersetcount--;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleDisk::PostUpdate()

{
	if (!destroyed)
	{
		SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect2);
	}
	return Update_Status::UPDATE_CONTINUE;
}

void ModuleDisk::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER)
	{
		if (App->player->blockdisk == true)
		{
			bloqueig = true;
		}
		if (timerblock <= 0) {
			App->player->personatgedisc = 1;

			position.x = App->player->position.x + 40;
			position.y = App->player->position.y + 10;

			disc_speed_X = 0;
			disc_speed_Y = 0;
			saque = 0;

			currentAnimation2 = &invisible;
		}
		
	}


	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER2)
	{
		
		App->player2->personatgedisc2 = 1;


		position.x = App->player2->position.x - 20;

		position.y = App->player2->position.y + 10;


		disc_speed_X = 0;
		disc_speed_Y = 0;
		saque = 0;

		currentAnimation2 = &invisible;

	}
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_1)
	{

		position.x = 143;
		position.y = 191;
		disc_speed_X = 0;
		disc_speed_Y = 0;




		timer = 120;
		App->propsBackground->timersetcount = 350;




		if (ultimplayer == 1) {

			if (godmode != 1) {
				score_player_1 += 5;
			}


			saque = 2;
		}

		if (ultimplayer == 2) {
			if (godmode != 1) {
				score_player_2 += 5;
			}

			saque = 1;
		}


	}
	else if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_2)
	{


		position.x = 143;
		position.y = 191;
		disc_speed_X = 0;
		disc_speed_Y = 0;




		timer = 120;

		App->propsBackground->timersetcount = 350;



		if (ultimplayer == 1) {
			if (godmode != 1) {
				score_player_1 += 3;
			}

			saque = 2;
		}

		if (ultimplayer == 2) {
			if (godmode != 1) {
				score_player_2 += 3;
			}
			saque = 1;
		}

	}
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::OBSTACLE1) { disc_speed_Y *= -1; }
}