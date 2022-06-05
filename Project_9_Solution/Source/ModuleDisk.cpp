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
	projectile.PushBack({ 171, 2, 23, 41 });
	projectile.PushBack({ 195, 2, 33, 42 });

	projectile.PushBack({ 229, 0, 43, 44 });
	projectile.PushBack({ 229, 148, 43, 44 });

	projectile.PushBack({ 195, 150, 33, 42 });
	projectile.PushBack({ 171, 150, 23, 41 });
	projectile.PushBack({ 145, 152, 21, 38 });
	projectile.PushBack({ 116, 153, 28, 36 });
	projectile.PushBack({ 79, 154, 36, 34 });
	projectile.PushBack({ 53, 155, 25, 31 });
	projectile.PushBack({ 35, 156, 17, 29 });

	projectile.loop = true;
	projectile.speed = 0.3f;

	invisible.PushBack({ 0,0,0,0 });

	blocking.PushBack({ 17, 29, 35, 8 });
	blocking.loop = true;
	blocking.speed = 0.2f;

	// Super Hiromi Mita
	hiromisupercharging.PushBack({0, 0, 64, 64});
	hiromisupercharging.PushBack({ 64, 0, 64, 64 });
	hiromisupercharging.PushBack({ 128, 0, 64, 64 });
	hiromisupercharging.PushBack({ 192, 0, 64, 64 });
	hiromisupercharging.PushBack({ 0, 64, 64, 64 });
	hiromisupercharging.PushBack({ 64, 64, 64, 64 });
	hiromisupercharging.PushBack({ 128, 64, 64, 64 });
	hiromisupercharging.PushBack({ 192, 64, 62, 63 });
	hiromisupercharging.PushBack({ 0, 128, 60, 60 });
	hiromisupercharging.PushBack({ 60, 128, 56, 56 });
	hiromisupercharging.PushBack({ 116, 128, 52, 52 });
	hiromisupercharging.PushBack({ 168, 128, 48, 48 });
	hiromisupercharging.PushBack({ 0, 188, 48, 48 });
	hiromisupercharging.PushBack({ 48, 188, 48, 48 });
	hiromisupercharging.PushBack({ 96, 188, 48, 48 });
	hiromisupercharging.PushBack({ 144, 188, 48, 48 });
	hiromisupercharging.PushBack({ 192, 188, 64, 64 });
	hiromisupercharging.PushBack({ 0, 236, 38, 38 });
	hiromisupercharging.PushBack({ 38, 236, 32, 32 });

	//Super Hiromi disk advance
	hiromisuper.PushBack({ 70, 236, 16, 96 });
	hiromisuper.PushBack({ 86, 236, 16, 84 });
	hiromisuper.PushBack({ 102, 236, 13, 38 });

	//Beeho Super cargando
	beehosupercharging.PushBack({0, 0, 43, 42});
	beehosupercharging.PushBack({ 43, 0, 41, 40 });
	beehosupercharging.PushBack({ 84, 0, 37, 37 });
	beehosupercharging.PushBack({ 121, 0, 53, 52 });
	beehosupercharging.PushBack({ 174, 0, 51, 45 });
	beehosupercharging.PushBack({ 0, 52, 38, 49 });
	beehosupercharging.PushBack({ 40, 52, 58, 53 });
	beehosupercharging.PushBack({ 98, 52, 50, 46 });
	beehosupercharging.PushBack({ 149, 52, 45, 45 });
	beehosupercharging.PushBack({ 194, 52, 45, 49 });

	//al lanzar ulti behoo
	beehosuperthrowing.PushBack({ 80, 156, 18, 19 });
	beehosuperthrowing.PushBack({ 98, 156, 16, 28 });
	beehosuperthrowing.PushBack({ 114, 156, 15, 45 });
	beehosuperthrowing.PushBack({ 129, 156, 48, 46 });
	beehosuperthrowing.PushBack({ 177, 156, 45, 48 });
	beehosuperthrowing.PushBack({ 0, 204, 38, 26 });

	//superb Arriba
	beehosuperUp.PushBack({ 470, 67, 16, 16 });
	beehosuperUp.PushBack({ 486, 67, 16, 16 });
	beehosuperUp.PushBack({ 256, 51, 16, 16 });

	//superb abajo
	beehosuperDown.PushBack({32, 156, 16, 15});
	beehosuperDown.PushBack({ 48, 156, 16, 16 });
	beehosuperDown.PushBack({ 64, 156, 16, 14 });

	//superb derecha
	beehosuperRight.PushBack({ 454, 0, 16, 16 });
	beehosuperRight.PushBack({ 272, 51, 16, 16 });

	//superb izquierda
	beehosuperLeft.PushBack({ 198, 105, 16, 16 });
	beehosuperLeft.PushBack({ 16, 156, 16, 16 });
	
	//superb chispas Arriba D->I
	beehosuperUpDI.PushBack({ 256, 0, 56, 44 });
	beehosuperUpDI.PushBack({ 396, 0, 58, 51 });
	beehosuperUpDI.PushBack({ 338, 0, 58, 48 });
	beehosuperUpDI.PushBack({ 312, 0, 26, 17 });

	//superb chispas Arriba I->D
	beehosuperUpID.PushBack({ 0, 105, 56, 44 });
	beehosuperUpID.PushBack({ 138, 105, 60, 51 });
	beehosuperUpID.PushBack({ 82, 105, 56, 48 });
	beehosuperUpID.PushBack({ 56, 105, 26, 17 });

	//superb chispas Abajo D->I
	beehosuperDownDI.PushBack({ 256, 118, 56, 44 });
	beehosuperDownDI.PushBack({ 394, 118, 58, 51 });
	beehosuperDownDI.PushBack({ 338, 118, 58, 48 });
	beehosuperDownDI.PushBack({ 312, 118, 26, 44 });

	//superb chispas Abajo I->D
	beehosuperDownID.PushBack({ 256, 67, 56, 44 });
	beehosuperDownID.PushBack({ 396, 67, 58, 51 });
	beehosuperDownID.PushBack({ 338, 67, 58, 48 });
	beehosuperDownID.PushBack({ 312, 67, 26, 44 });

	//klausssuperamunt
	klausssuperD.PushBack({ 639, 0, 54, 96 });
	klausssuperD.PushBack({ 519, 0, 120, 96 });
	klausssuperD.PushBack({ 161, 433, 141, 96 });
	klausssuperD.PushBack({ 333, 285, 237, 96 });

	//klausssuper abaix
	klausssuperU.PushBack({ 1153, 509, 96, 54 });
	klausssuperU.PushBack({ 237, 285, 96, 69 });
	klausssuperU.PushBack({ 1057, 477, 96, 86 });
	klausssuperU.PushBack({ 141, 285, 96, 99 });

	// Klauss super dreta
	klausssuperR.PushBack({ 639, 0, 54, 96 });
	klausssuperR.PushBack({ 519, 0, 120, 96 });
	klausssuperR.PushBack({ 161, 433, 141, 96 });
	klausssuperR.PushBack({ 333, 285, 237, 96 });

	//klauss super esquerra
	klausssuperL.PushBack({ 1119, 0, 54, 96 });
	klausssuperL.PushBack({ 1173, 0, 120, 96 });
	klausssuperL.PushBack({ 1153, 241, 141, 96 });
	klausssuperL.PushBack({ 1057, 122, 237, 96 });

	//klauss inicio tiro
	klausssuperinicio.PushBack({ 264, 731, 144, 143 });
	klausssuperinicio.PushBack({ 96, 731, 168, 168 });
	klausssuperinicio.PushBack({ 792, 537, 194, 194 });
	klausssuperinicio.PushBack({ 598, 433, 192, 194 });
	klausssuperinicio.PushBack({ 309, 433, 192, 192 });

	//gol ulti klauss
	klausssupergol.PushBack({ 408, 731, 285, 285 });
	klausssupergol.PushBack({ 0, 0, 285, 285 });

	//canvia sentit 
	klausssupersentit.PushBack({ 0, 285, 141, 141 });
	klausssupersentit.PushBack({ 11, 435, 141, 141 });
	klausssupersentit.PushBack({ 693, 731, 141, 141 });
	klausssupersentit.PushBack({ 584, 292, 141, 141 });

	//choca jugador
	klausssuperchocar.PushBack({ 285, 0, 234, 255 });



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
	ultimate_disk = false;
	muerte_subita = false;
	timer = 120;
	timer_Win = 300;
	timerterrap1=0;
	timerterrap2 = 0;
	texture = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");
	texturevolea = App->textures->Load("Assets/UI/Volea_Caiguda_Frisbee.png");
	marca = App->textures->Load("Assets/UI/Others/MarcaF1.png");
	superhiromitexture = App->textures->Load("Assets/Sprites/Characters/Hiromi_Mita/SuperShotEffects.png");
	superbeehotexture = App->textures->Load("Assets/Sprites/Characters/Beeho_Yoo/superShotEffectsSpriteSheet.png");
	superklausstexture = App->textures->Load("Assets/Sprites/Characters/Klauss_Wessel/Aleman_SuperShot.png");

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
	augmentvx = 0;
	augmentvy = 0;
	aux = 0;
	aux2 = 0;
	sentido = 0;

	 personaje = 3;

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


	
	     if (position.x == volea_x) {					//disc cau a terra
				volea = false;
				onair = false;
				disc_speed_X = 0;
				disc_speed_Y = 0;
				correcciospritex = -9;
				correcciospritey = -10;

				if (App->player->personatgedisc != 1 && ultimplayer ==1 && App->player2->currentAnimation != &App->player2->charge_ult)

				{
					timerterrap1 = 60;
					
					App->audio->PlayFx(landingfx, 0);
				
				}
				
				if (currentAnimation2 != &terraanim) {
					terraanim.Reset();
				}
				currentAnimation2 = &terraanim;
				if (App->player2->personatgedisc2 != 1 && ultimplayer ==2 && App->player->currentAnimation != &App->player->charge_ult)
				{
					App->audio->PlayFx(landingfx, 0);
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
			saque = 2;
			App->audio->PlayFx(Pts2, 0);
			currentAnimation2 = &idle;


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
			saque = 1;
			App->audio->PlayFx(Pts2, 0);
			currentAnimation2 = &idle;
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

			currentAnimation2 = &moving;

		}

		if (saque == -2 && timer == 0 && timer_set <= 0) {



			disc_speed_X = 3;
			disc_speed_Y = -2;
			currentAnimation2 = &moving;


		}

		if (saque == 1 && timer == 0 && timer_set <= 0) {



			disc_speed_X = -3;
			disc_speed_Y = -2;

			currentAnimation2 = &moving;

		}

		if (saque == 2 && timer == 0 && timer_set <= 0) {



			disc_speed_X = 3;
			disc_speed_Y = -2;

			currentAnimation2 = &moving;

		}



		if (bloqueig == true) {


			onair = true;

			disc_speed_X = 0;
			disc_speed_Y = 0;
			timerblock = 60;
			bloqueig = false;
			if (ultimplayer == 1) { position.x += 20;  volea_x = position.x;	position.y -= 20;  volea_y = position.y+30; }
			else {
				position.x -= 20;
				position.y -= 20;
				volea_x = position.x ;
				volea_y = position.y+20;
			}

		}

		if (timerblock > 0) {
			currentAnimation2 = &projectile;
			App->audio->PlayFx(onairfx, 0);
			timerblock--;
		}

		if (timerblock == 0 && volea == false) {
			onair = false;

		}

	
		if (ultimate_disk == true) {
		
			
			if (personaje == 3) {
				if (sentido == 1) {
					if (position.y >= aux2 - 40) {

						augmentvx = 0;
						augmentvy = -3;
					}

					if (position.y < aux2 - 40) {

						augmentvx = 3;
						augmentvy = 0;
					}

					if (position.x >= aux + 80) {

						augmentvx = 0;
						augmentvy = 3;
					}

					if (position.y >= aux2 + 40) {

						augmentvx = 3.3;
						augmentvy = 0;

					}

				}
				else if (sentido == -1) {
					if (position.y <= aux2 + 40) {

						augmentvx = 0;
						augmentvy = 3;
					}

					if (position.y > aux2 + 40) {

						augmentvx = 3;
						augmentvy = 0;
					}

					if (position.x >= aux + 80) {

						augmentvx = 0;
						augmentvy = -3;
					}

					if (position.y <= aux2 - 40) {

						augmentvx = 3.3;
						augmentvy = 0;

					}





				}
				currentAnimation2 = &moving;
				position.x += augmentvx;
				position.y += augmentvy;

			}
			else {


				augmentvy = (-sin(augmentvx / 30) * 55) * sentido;
				augmentvx += disc_speed_X;
				position.x = aux + augmentvx;
				position.y = aux2 + augmentvy;
			}
		} 
		else {
			aux = 0;
			aux = 0;
			augmentvx = 0;
			augmentvy = 0;
			position.x += disc_speed_X;
			position.y += disc_speed_Y;
		}
		

		
	
	
	

		


	

		
		

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
	if (volea == true ) {

		SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
		App->render->Blit(texturevolea, position.x, position.y, &rect2);
		
		App->render->Blit(marca, volea_x, volea_y, NULL);

	}
	if (onair == true) {
		App->render->Blit(marca, volea_x, volea_y, NULL);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleDisk::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER && onair==false)
	{
		
		ultimate_disk = false;


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
		ultimate_disk = false;
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
		ultimate_disk = false;
		App->sceneLevel_1->moureCameraGol = true;
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
		App->sceneLevel_1->moureCameraGol = true;
		ultimate_disk = false;
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
		
		if (ultimate_disk == true) {

			augmentvx = 1;
			augmentvy = 0;
			aux = position.x;
			aux2 = position.y;
			sentido = -1;


		}
		else if (onair == false) {
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

		if (ultimate_disk == true) {

			augmentvx = 1;
			augmentvy = 0;
		
			aux = position.x;
			aux2 = position.y;
			sentido = 1;


		} else if (saque == 0 && onair == false) {
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