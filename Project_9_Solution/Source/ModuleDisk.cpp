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

	// Super Hiromi Mita
	hiromisuper.PushBack({0, 0, 64, 64});
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });
	hiromisuper.PushBack({ 0, 0, 64, 64 });




	voleaanim.PushBack({ 20, 20, 20, 19});
	voleaanim.PushBack({ 80, 20, 24, 21 });
	voleaanim.PushBack({ 144, 20, 24, 24 });
	voleaanim.PushBack({ 208, 20, 28, 26 });
	voleaanim.PushBack({ 276, 20, 28, 28 });
	voleaanim.PushBack({ 345, 20, 32, 30 });
	voleaanim.PushBack({ 416, 20, 32, 32 });
	voleaanim.PushBack({ 488, 20, 36, 33 });
	voleaanim.PushBack({ 564, 20, 36, 35 });
	voleaanim.PushBack({ 640, 20, 36, 36 });
	voleaanim.PushBack({ 716, 20, 40, 37 });
	voleaanim.PushBack({ 796, 20, 40, 39 });
	voleaanim.PushBack({ 876, 20, 40, 40 });
	voleaanim.PushBack({ 956, 20, 40, 40 });
	voleaanim.PushBack({ 1036, 20, 43, 41 });
	voleaanim.PushBack({ 1119, 20, 43, 42 });
	voleaanim.PushBack({ 1202, 20, 43, 43 });
	voleaanim.PushBack({ 1285, 20, 43, 43 });
	voleaanim.PushBack({ 1368, 20, 43, 43 });
	voleaanim.PushBack({ 1451, 20, 43, 42 });
	voleaanim.PushBack({ 1534, 20, 43, 43 });
	voleaanim.PushBack({ 1617, 20, 43, 44 });
	voleaanim.PushBack({ 1700, 20, 43, 44 });
	voleaanim.PushBack({ 1783, 20, 43, 44 });
	voleaanim.PushBack({ 1866, 20, 43, 44 });
	voleaanim.PushBack({ 1949, 20, 43, 44 });
	voleaanim.PushBack({ 2032, 20, 43, 44 });
	voleaanim.PushBack({ 2115, 20, 43, 43 });
	voleaanim.PushBack({ 2198, 20, 43, 43 });
	voleaanim.PushBack({ 2281, 20, 43, 43 });
	voleaanim.PushBack({ 2364, 20, 43, 42 });
	voleaanim.PushBack({ 2447, 20, 43, 41 });
	voleaanim.PushBack({ 2530, 20, 43, 41 });
	voleaanim.PushBack({ 2613, 20, 40, 40 });
	voleaanim.PushBack({ 2693, 20, 40, 39 });
	voleaanim.PushBack({ 2773, 20, 40, 38 });
	voleaanim.PushBack({ 2853, 20, 40, 38 });
	voleaanim.PushBack({ 2933, 20, 40, 37 });
	voleaanim.PushBack({ 3013, 20, 36, 36 });
	voleaanim.PushBack({ 3089, 20, 36, 35 });
	voleaanim.PushBack({ 3165, 20, 36, 34 });
	voleaanim.PushBack({ 3241, 20, 32, 32 });
	voleaanim.PushBack({ 3313, 20, 32, 31 });
	voleaanim.PushBack({ 3385, 20, 32, 30 });
	voleaanim.PushBack({ 3457, 20, 32, 29 });
	voleaanim.PushBack({ 3529, 20, 28, 28 });
	voleaanim.PushBack({ 3597, 20, 28, 26 });
	voleaanim.PushBack({ 3665, 20, 28, 25 });
	voleaanim.PushBack({ 3733, 20, 24, 23 });
	voleaanim.PushBack({ 3797, 20, 24, 22 });
	voleaanim.PushBack({ 3861, 20, 24, 21 });
	voleaanim.PushBack({ 3925, 20, 20, 19 });
	voleaanim.PushBack({ 3985, 20, 20, 17 });
	voleaanim.PushBack({ 4045, 20, 16, 16 });
	voleaanim.PushBack({ 4101, 20, 16, 16 });
	voleaanim.PushBack({ 4157, 20, 16, 16 });
	voleaanim.PushBack({ 4213, 20, 16, 16 });
	voleaanim.PushBack({ 4269, 20, 16, 16 });
	voleaanim.loop = false;
	voleaanim.speed = 0.95f;

	terraanim.PushBack({ 0, 71, 32, 32});
	terraanim.PushBack({ 33, 71, 32, 32 });
	terraanim.PushBack({ 65, 71, 32, 32 });
	terraanim.PushBack({ 97, 71, 32, 32 });
	terraanim.PushBack({ 129, 71, 32, 32 });
	terraanim.PushBack({ 161, 71, 32, 32 });
	terraanim.PushBack({ 193, 71, 32, 32 });
	terraanim.PushBack({ 225, 71, 32, 32 });
	terraanim.PushBack({ 257, 71, 32, 32 });
	terraanim.PushBack({ 0, 103, 32, 32 });
	terraanim.PushBack({ 33, 103, 32, 32 });
	terraanim.PushBack({ 65, 103, 32, 32 });
	terraanim.PushBack({ 97, 103, 32, 32 });
	terraanim.PushBack({ 129, 103, 32, 32 });
	terraanim.PushBack({ 161, 103, 32, 32 });
	terraanim.PushBack({ 193, 103, 32, 32 });
	terraanim.PushBack({ 225, 103, 32, 32 });
	terraanim.loop = false;
	terraanim.speed = 1.0f;




}

ModuleDisk::~ModuleDisk()
{

}

bool ModuleDisk::Start()
{
	App->collisions->Enable();

	currentAnimation2 = &idle;
	correcciospritex = 0;
	correcciospritey = 0;

	LOG("Loading Disk textures");
	si = 0;
	bool ret = true;
	muerte_subita = false;
	timer = 120;
	timer_Win = 300;
	timerterrap1=0;
	timerterrap2 = 0;
	texture = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");
	texturevolea = App->textures->Load("Assets/UI/Volea_Caiguda_Frisbee.png");
	marca = App->textures->Load("Assets/UI/Others/MarcaF1.png");
	superhiromi = App->textures->Load("Assets/Sprites/Characters/Hiromi_Mita/SuperShotEffects.png");

	blockfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Block.wav");
	catchfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Catch.wav");
	onairfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Frisbee/Freesbeonair.wav");

	//audio comentarista
	Pts2 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/2Pts.wav");
	Pts3 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/3Pts.wav");
	Pts5 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/5Pts.wav");
	CongratulationsWinner = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Congratulations Winner.wav");
	ExcelentGame = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Excelent Game.wav");
	FinalRound = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Final Round.wav");
	GameSet = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Game Set.wav");
	GetReady = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Get Ready.wav");
	GoodGame = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Good Game.wav");
	Miss = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Miss.wav");
	Out = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Out.wav");
	Round1 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Round1.wav");
	Round2 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Round2.wav");
	Round3 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Round3.wav");
	Round4 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Round4.wav");
	Round5 = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Round5.wav");
	Set = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Set.wav");
	Spear = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Spear.wav");
	Strike = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Strike.wav");
	WellDone = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Well Done.wav");
	Wow = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Wow.wav");
	Ya = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Comentarist/Ya!.wav");

	position.x = 145; //Posicio arbitre
	position.y = 191; //posicio arbitre

	onair = false;
	bloqueig = false;
	godmode = false;

	destroyed = false;

	diskcollider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::DISK, this);
	super_zone_collider = App->collisions->AddCollider({ volea_x,volea_y,10,10 }, Collider::Type::SUPER_ZONE, this);

	App->audio->PlayFx(Round1, 0);

	return ret;
}

Update_Status ModuleDisk::Update()
{
	if (sets_player1 == 2 && sets_player2 == 2) {

		if (score_player_1 > score_player_2) {

			sets_player2 -= 1;
			muerte_subita = false;

		}

		if (score_player_2 > score_player_1) {

			sets_player1 -= 1;
			muerte_subita = false;

		}

	}
	if (App->sceneLevel_1->timer2 == 0 && (App->player->personatgedisc == 1 || App->player2->personatgedisc2 == 1)) {

		if (godmode != true)
		{
			if (score_player_1 > score_player_2) {

				sets_player1 += 1;
				saque = -2;
				sets += 1;
				App->audio->PlayFx(Set, 0);
				timer_set = 600;

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
				App->audio->PlayFx(Set, 0);
				timer_set = 600;

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
					App->audio->PlayFx(Set, 0);
					timer_set = 600;

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

	if ((sets_player1 == 2 || sets_player2 == 2) && si == 1 && muerte_subita == false) {

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
		if (currentAnimation2 != &voleaanim) {
			voleaanim.Reset();
		}

		currentAnimation2 = &voleaanim;


		if (position.x >= 300 && ultimplayer == 1) {		//disc cau a terra
			volea = false;
			onair = false;
			disc_speed_X = 0;
			disc_speed_Y = 0;
			correcciospritex = -9;
			correcciospritey = -10;
			if (currentAnimation2 != &terraanim) {
				terraanim.Reset();
			}
			currentAnimation2 = &terraanim;
			if (App->player->personatgedisc != 1)

			{
				timerterrap1 = 60;
				App->player->scoreplayer1 += 2;
				App->player->position.x = 38;
				App->player->position.y = 112;
				App->audio->PlayFx(landingfx, 0);
				App->audio->PlayFx(Pts2, 0);
				saque = 1;
				timerterrap1 = 60;
			}
		}

			else if (position.x == volea_x) {					//disc cau a terra
				volea = false;
				onair = false;
				disc_speed_X = 0;
				disc_speed_Y = 0;
				correcciospritex = -9;
				correcciospritey = -10;
				if (currentAnimation2 != &terraanim) {
					terraanim.Reset();
				}
				currentAnimation2 = &terraanim;
				if (App->player2->personatgedisc2 != 1)
				{

					timerterrap2 = 60;

				}
			}
			else if (position.x <= 20 && ultimplayer == 2) {
				volea = false;
				onair = false;
				disc_speed_X = 0;
				disc_speed_Y = 0;
				currentAnimation2 = &moving;
			}

		
	}
		if (timerterrap1 == 1) {
			position.x = 143;
			position.y = 191;
			correcciospritex = 0;
			correcciospritey = 0;
			App->disk->score_player_1 += 2;
			App->player->position.x = 38;
			App->player->position.y = 112;
			timer = 120;
			App->propsBackground->timersetcount = 350;
			saque = 1;
			App->audio->PlayFx(Pts2, 0);


		}
		if (timerterrap2 == 1) {
			position.x = 143;
			position.y = 191;
			correcciospritex = 0;
			correcciospritey = 0;
			App->disk->score_player_2 += 2;
			App->player2->position.x = 240;
			App->player2->position.y = 112;
			timer = 120;
			App->propsBackground->timersetcount = 350;
			saque = 2;
			App->audio->PlayFx(Pts2, 0);

		}
		if (score_player_1 >= 12) {

			sets_player1 += 1;
			sets += 1;
			saque = -2;
			timer_set = 600;
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

			timer_set = 600;
			score_player_1 = 0;
			score_player_2 = 0;
			App->player->currentAnimation = &App->player->rightidleAnim;
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
	

		if (timer_set == 301)
		{
			App->audio->PlayFx(GetReady, 0);
		}

		if (saque == -1 && timer == 0 && timer_set <= 0) {



			disc_speed_X = -3;
			disc_speed_Y = -2;



		}

		if (saque == -2 && timer == 0 && timer_set <= 0) {



			disc_speed_X = 3;
			disc_speed_Y = -2;



		}

		if (saque == 1 && timer == 0 && timer_set <= 0) {



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

		if (timerblock == 0 && volea == false) {
			onair = false;

		}

	


	position.x += disc_speed_X;
	position.y += disc_speed_Y;
	diskcollider->SetPos(position.x, position.y);
	super_zone_collider->SetPos(volea_x, volea_y);

	currentAnimation2->Update();

	App->propsBackground->timersetcount--;
	timerterrap1--;
	timerterrap2--;
	
	return Update_Status::UPDATE_CONTINUE;

}

Update_Status ModuleDisk::PostUpdate()

{
	if (!destroyed)
	{
		SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
		
        App->render->Blit(texture, position.x + correcciospritex, position.y + correcciospritey, &rect2);
		
		


	}
	if (volea == true) {

		SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
		App->render->Blit(texturevolea, position.x, position.y, &rect2);
		App->render->Blit(marca, volea_x, volea_y, NULL);

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
		if (App->player2->blockdisk == false) {

			App->audio->PlayFx(catchfx, 0);
			App->player2->currentAnimation = &App->player2->recive;
			App->player2->personatgedisc2 = 1;

			position.x = App->player2->position.x - 20;
			position.y = App->player2->position.y + 10;

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
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::SCOREZONE_1)
	{
		if (ultimplayer == 1) {
			if (position.y < 127) {
				App->sceneLevel_1->points5righttop = 1;
				App->sceneLevel_1->timerofpoints = 120;
				App->sceneLevel_1->Points5ScoreR.Reset();
			}
			else if (position.y > 127) {
				App->sceneLevel_1->points5rightbot = 1;
				App->sceneLevel_1->timerofpoints = 120;
				App->sceneLevel_1->Points5ScoreR.Reset();
			}
			if (godmode != true) {
				score_player_1 += 5;
				App->audio->PlayFx(Pts5, 0);
			}

			saque = 2;
		}
		if (ultimplayer == 2) {
			if (position.y < 127) {
				App->sceneLevel_1->points5lefttop = 1;
				App->sceneLevel_1->timerofpoints = 120;
				App->sceneLevel_1->Points5ScoreL.Reset();
			}
			if (position.y > 127) {
				App->sceneLevel_1->points5leftbot = 1;
				App->sceneLevel_1->timerofpoints = 120;
				App->sceneLevel_1->Points5ScoreL.Reset();
			}
			if (godmode != true) {
				score_player_2 += 5;
				App->audio->PlayFx(Pts5, 0);
			}

			saque = 1;
		}
		disc_speed_X = 0;
		disc_speed_Y = 0;
		position.x = 143;		//disc torna al arbitre quan fas gol
		position.y = 191;

		timer = 120;
		App->propsBackground->timersetcount = 350;

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
			
			App->sceneLevel_1->points3right = 1;
			App->sceneLevel_1->timerofpoints = 120;
			App->sceneLevel_1->Points3ScoreR.Reset();
			
			if (godmode != true) {
				score_player_1 += 3;
				App->audio->PlayFx(Pts3, 0);
			}

			saque = 2;
		}

		if (ultimplayer == 2) {
			App->sceneLevel_1->points3left = 1;
			App->sceneLevel_1->timerofpoints = 120;
			App->sceneLevel_1->Points3ScoreL.Reset();
			if (godmode != true) {
				score_player_2 += 3;
				App->audio->PlayFx(Pts3, 0);
			}
			saque = 1;
		}

	}
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::OBSTACLE1) {
		if (volea == false)
			disc_speed_Y *= -1;
	}

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::TOP_WALL) {
		
			if (onair == false) {
				disc_speed_Y = -disc_speed_Y;
			}
			else {
				volea = false;
				onair = false;
				position.y += 10;
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

	if (c1->type == Collider::Type::SUPER_ZONE && c2->type == Collider::Type::PLAYER && volea == true){



	}

	if (c1->type == Collider::Type::SUPER_ZONE && c2->type == Collider::Type::PLAYER2 && volea == true) {



	}
}