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

	idle.PushBack({ 117, 48, 16, 16 });
	idle.loop = false;

	// Projectile motion animation
	projectile.PushBack({ 35, 8, 17, 29 });
	projectile.PushBack({ 53, 7, 25, 31 });
	projectile.PushBack({ 79, 6, 36, 34 });
	projectile.PushBack({ 116, 5, 28, 36 });
	projectile.PushBack({ 145, 4, 21, 38 });
	projectile.PushBack({ 167, 3, 3, 39 });
	projectile.PushBack({ 171, 2, 23, 41 });
	projectile.PushBack({ 195, 2, 33, 42 });

	projectile.PushBack({ 229, 0, 43, 44 });

	projectile.PushBack({ 195, 2, 33, 42 });
	projectile.PushBack({ 171, 2, 23, 41 });
	projectile.PushBack({ 167, 3, 3, 39 });
	projectile.PushBack({ 145, 4, 21, 38 });
	projectile.PushBack({ 116, 5, 28, 36 });
	projectile.PushBack({ 79, 6, 36, 34 });
	projectile.PushBack({ 53, 7, 25, 31 });
	projectile.PushBack({ 35, 8, 17, 29 });

	projectile.loop = true;
	projectile.speed = 0.3f;

	invisible.PushBack({ 0,0,0,0 });

	blocking.PushBack({ 17, 29, 35, 8 });
	blocking.loop = true;
	blocking.speed = 0.2f;

	voleaanim.PushBack({ });

}

ModuleDisk::~ModuleDisk()
{

}

bool ModuleDisk::Start()
{
	App->collisions->Enable();

	currentAnimation2 = &idle;


	LOG("Loading Disk textures");

	si = 0;
	bool ret = true;
	muerte_subita = false;
	timer = 120;
	timer_Win = 300;

	texture = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");
	texturevolea = App->textures->Load("Assets/UI/Volea_Caiguda_Frisbee.png");

	blockfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Block.wav");
	catchfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Catch.wav");
	onairfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Freesbeonair.wav");

	position.x = 145; //Posicio arbitre
	position.y = 191; //posicio arbitre

	onair = false;
	bloqueig = false;
	godmode = false;

	destroyed = false;

	diskcollider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::DISK, this);

	return ret;
}

Update_Status ModuleDisk::Update()
{
	if (sets_player1==2 && sets_player2==2) {

		if (score_player_1 > score_player_2) {

			sets_player2 -= 1;
			muerte_subita = false;

		}

		if (score_player_2 > score_player_1) {

			sets_player1 -= 1;
			muerte_subita = false;

		}

	}
	if (App->sceneLevel_1->timer2 == 0 && (App->player->personatgedisc==1 || App->player2->personatgedisc2==1)) {

		if (godmode != true)
		{
			if (score_player_1 > score_player_2) {

				sets_player1 += 1;
				saque = -2;
				sets += 1;
				timer_set = 300;
				score_player_1 = 0;
				score_player_2 = 0;
				App->player->currentAnimation = &App->player->rightidleAnim;
				App->player2->currentAnimation = &App->player2->leftidleAnim;
				position.x = 143;
				position.y = 191;
				App->sceneLevel_1->timer2 = 1800;
				App->sceneLevel_1->timer.Reset();
				App->propsBackground->timersetcount = 350;
				currentAnimation2 = &idle;
			}

			else if (score_player_2 > score_player_1) {

				sets_player2 += 1;
				saque = -1;
				sets += 1;
				timer_set = 300;
				score_player_1 = 0;
				score_player_2 = 0;
				App->player->currentAnimation = &App->player->rightidleAnim;
				App->player2->currentAnimation = &App->player2->leftidleAnim;
				position.x = 143;
				position.y = 191;
				App->sceneLevel_1->timer2 = 1800;
				App->sceneLevel_1->timer.Reset();
				App->propsBackground->timersetcount = 350;
				currentAnimation2 = &idle;
			}

			else if (score_player_1 == score_player_2) {


				sets_player1 += 1;
				sets_player2 += 1;
				if (sets_player1 == 2 && sets_player2 == 2) {

					muerte_subita = true;
					saque = -1;
					sets += 1;
					timer_set = 300;
					score_player_1 = 0;
					score_player_2 = 0;
					App->player->currentAnimation = &App->player->rightidleAnim;
					App->player2->currentAnimation = &App->player2->leftidleAnim;
					position.x = 143;
					position.y = 191;
					App->sceneLevel_1->timer2 = 1800;
					App->sceneLevel_1->timer.Reset();
					App->propsBackground->timersetcount = 350;
					currentAnimation2 = &idle;

				}
				else {

					saque = -1;
					sets += 1;
					timer_set = 300;
					score_player_1 = 0;
					score_player_2 = 0;
					App->player->currentAnimation = &App->player->rightidleAnim;
					App->player2->currentAnimation = &App->player2->leftidleAnim;
					position.x = 143;
					position.y = 191;
					App->sceneLevel_1->timer2 = 1800;
					App->sceneLevel_1->timer.Reset();
					App->propsBackground->timersetcount = 350;
					currentAnimation2 = &idle;
				}


			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN && godmode == false) {
		godmode = true;
	}
	else
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN && godmode == true) {
		godmode = false;
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

			saque = -1;

			App->sceneLevel_1->Disable();

			App->sceneIntroSNK->Enable();

			App->collisions->Disable();
		

		}
	}
	
	if (volea == true)			//volea
	{
		onair = true;

		
		currentAnimation2 = &projectile;

		/*voleaanimation = &voleaanim;*/
		disc_speed_X = 2.5;

		if (position.x >= 250 && ultimplayer == 1) {
			volea = false;
			onair = false;
			disc_speed_X = 0;
			disc_speed_Y = 0;
			currentAnimation2 = &idle;
		}
		else if (position.x == volea_x) {
			volea = false;
			onair = false;
			disc_speed_X = 0;
			disc_speed_Y = 0;
			currentAnimation2 = &idle;
		}
		else if (position.x <= 38 && ultimplayer == 2) {
			volea = false;
			onair = false;
			disc_speed_X = 0;
			disc_speed_Y = 0;
			currentAnimation2 = &idle;
		}
	}

	if (score_player_1 >= 12) {

		sets_player1 += 1;
		sets += 1;
		saque = -2;
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
		saque = -1;

		timer_set = 300;
		score_player_1 = 0;
		score_player_2 = 0;
		App->player->currentAnimation= &App->player->rightidleAnim;
		App->player2->currentAnimation = &App->player2->leftidleAnim;
		App->sceneLevel_1->timer.Reset();
	}

	if (saque == 1 || saque == 2 || saque == -1 || saque == -2) {
		App->player->personatgedisc = -1;
		App->player2->personatgedisc2 = -1;
		if (timer > 0) {
			timer -= 1;
		}
		timer_set -= 1;
		App->player->position.x = 38;
		App->player->position.y = 112;

		App->player2->position.x = 240;
		App->player2->position.y = 112;
		volea = false;
    }
	
	if (saque == -1 && timer == 0 && timer_set <= 0) {



		disc_speed_X = -3;
		disc_speed_Y = -2;



	}

	if (saque == -2 && timer == 0 && timer_set <= 0) {



		disc_speed_X = 3;
		disc_speed_Y = -2;



	}
	
	if (saque == 1  && timer ==0 && timer_set <= 0 ) {

		

		disc_speed_X = -3;
		disc_speed_Y = -2;



	}

	if (saque == 2 && timer == 0 && timer_set <= 0) {



		disc_speed_X = 3;
		disc_speed_Y = -2;



	}



	if (bloqueig == true) {

		
		onair = true;

		disc_speed_X = 0;
		disc_speed_Y = 0;
		timerblock = 60;
		bloqueig = false;
		
	}

	if (timerblock > 0) {
		currentAnimation2 = &projectile;
		App->audio->PlayFx(onairfx, 0);
		timerblock--;
	}

	if (timerblock == 0 && volea == false ) {
		onair = false;
		
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
		App->render->Blit(texturevolea, position.x, position.y, &(voleaanim.GetCurrentFrame()));


	}
	return Update_Status::UPDATE_CONTINUE;
}

void ModuleDisk::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER && onair==false)
	{
		
		

		if (App->player->blockdisk == false) {
			App->audio->PlayFx(catchfx, 0);
			App->player->currentAnimation = &App->player->recive;
			App->player->personatgedisc = 1;

			position.x = App->player->position.x + 40;
			position.y = App->player->position.y + 10;

			disc_speed_X = 0;
			disc_speed_Y = 0;
			saque = 0;

			currentAnimation2 = &invisible;
			projectile.Reset();
		
		}
		else {

			bloqueig = true;

			App->audio->PlayFx(blockfx, 0);
		}
		
		
	}


	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER2 && onair == false)
	{
		
		App->player2->personatgedisc2 = 1;


		position.x = App->player2->position.x - 20;

		position.y = App->player2->position.y + 10;


		disc_speed_X = 0;
		disc_speed_Y = 0;
		saque = 0;

		currentAnimation2 = &invisible;
		projectile.Reset();

	}
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_1)
	{
		disc_speed_X = 0;
		disc_speed_Y = 0;
		position.x = 143;		//disc torna al arbitre quan fas gol
		position.y = 191;

		timer = 120;
		App->propsBackground->timersetcount = 350;




		if (ultimplayer == 1) {

			if (godmode != true) {
				score_player_1 += 5;
			}


			saque = 2;
		}

		if (ultimplayer == 2) {
			if (godmode != true) {
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
			if (godmode != true) {
				score_player_1 += 3;
			}

			saque = 2;
		}

		if (ultimplayer == 2) {
			if (godmode != true) {
				score_player_2 += 3;
			}
			saque = 1;
		}

	}
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::OBSTACLE1 && onair == false) { disc_speed_Y *= -1; }

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::TOP_WALL) {
		
			if (onair == false) {
				disc_speed_Y = -disc_speed_Y;
			}
			else {
				volea = false;
				onair = false;
				disc_speed_X = 0;
				disc_speed_Y = 0;
				currentAnimation2 = &idle;

			}
		
	}

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::BOT_WALL) {
		if (saque == 0 && onair == false) {
			disc_speed_Y = -disc_speed_Y;
		}
		else {
			volea = false;
			onair = false;
			disc_speed_X = 0;
			disc_speed_Y = 0;
			currentAnimation2 = &idle;
		}
	}
}