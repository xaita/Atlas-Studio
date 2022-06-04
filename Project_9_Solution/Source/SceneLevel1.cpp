#include "SceneLevel1.h"

#include <stdio.h>

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleDisk.h"
#include "PropsBackground.h"
#include "SDL/include/SDL.h"



SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	moureCameraGol = '1';

	bgTexture = App->textures->Load("Assets/Sprites/Stages/Concrete/concrete-sprite-sheet.png");				//BG CONCRETE + PROPS
	bgTopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/top_wall.png");								//
	bgExtremetopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall.png");				//
	bgExtremetopwallright = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall_Right.png");
	bgObstacle = App->textures->Load("Assets/Sprites/Stages/Concrete/obstacle.png");	//
	bgNet = App->textures->Load("Assets/Sprites/Stages/Concrete/net.png");										//
	UI = App->textures->Load("Assets/UI/UISpriteSheet_Upgrade.png");
	P1Win = App->textures->Load("Assets/UI/Others/P1Win.png");
	P2Win = App->textures->Load("Assets/UI/Others/P2Win.png");
	Points5scoreR = App->textures->Load("Assets/UI/Points_Goal/3_points_goal_(right)/3_points_dreta_2.png");


	UI_Timer = App->textures->Load("Assets/UI/timerSpriteSheet.png");

	

	App->audio->PlayMusic("Assets/Audios/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", 1.0f);					//MUSICA

	spectators.PushBack({ 0,0,358,224 });																		//ANIMACIO ESPECTADORS
	spectators.PushBack({ 363,0,358,224 });
	spectators.PushBack({ 739,0,358,224 });
	spectators.loop = true;
	spectators.speed = 0.15f;

	//int x = 15;
	//for (int i = 0; i < 32; i++) {
	//	timer.PushBack({ x,0,15,15 });
	//		x += 15;
	//}


	timer.PushBack({ 15,0,15,15 });
	timer.PushBack({ 30,0,15,15 });
	timer.PushBack({ 45,0,15,15 });
	timer.PushBack({ 60,0,15,15 });
	timer.PushBack({ 75,0,15,15 });
	timer.PushBack({ 90,0,15,15 });
	timer.PushBack({ 105,0,15,15 });
	timer.PushBack({ 120,0,15,15 });
	timer.PushBack({ 135,0,15,15 });
	timer.PushBack({ 150,0,15,15 });
	timer.PushBack({ 165,0,15,15 });
	timer.PushBack({ 180,0,15,15 });
	timer.PushBack({ 195,0,15,15 });
	timer.PushBack({ 210,0,15,15 });
	timer.PushBack({ 225,0,15,15 });
	timer.PushBack({ 240,0,15,15 });
	timer.PushBack({ 255,0,15,15 });
	timer.PushBack({ 270,0,15,15 });
	timer.PushBack({ 285,0,15,15 });
	timer.PushBack({ 300,0,15,15 });
	timer.PushBack({ 315,0,15,15 });
	timer.PushBack({ 330,0,15,15 });
	timer.PushBack({ 345,0,15,15 });
	timer.PushBack({ 360,0,15,15 });
	timer.PushBack({ 375,0,15,15 });
	timer.PushBack({ 390,0,15,15 });
	timer.PushBack({ 405,0,15,15 });
	timer.PushBack({ 420,0,15,15 });
	timer.PushBack({ 435,0,15,15 });
	timer.PushBack({ 450,0,15,15 });
	timer.PushBack({ 465,0,15,15 });
	timer.PushBack({ 480,0,15,15 });
	timer.loop = false;
	
	
	timer.speed = 0.017f;
	timer2 = 1800;

	Points5ScoreR.PushBack({ 300, 26, 0, 0 });

	//porteria esquerra
	App->collisions->AddCollider({ 0, 26, 1, 24 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 0, 170, 1, 24 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 0, 66, 1, 89 }, Collider::Type::SCOREZONE_2);

	//porteria dreta
	App->collisions->AddCollider({ 300, 26, 1, 24 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 300, 170, 1, 24 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 300, 66, 1, 89 }, Collider::Type::SCOREZONE_2);

	//parets
	App->collisions->AddCollider({ 0, 214, 304, 29 }, Collider::Type::BOT_WALL);
	App->collisions->AddCollider({ 0, 0, 304, 29 }, Collider::Type::TOP_WALL);

	//obstaculos red
	App->collisions->AddCollider({ 144, 70, 15, 14 }, Collider::Type::OBSTACLE1);
	App->collisions->AddCollider({ 144, 166, 15, 14 }, Collider::Type::OBSTACLE1);

	App->player->Enable();
	App->player2->Enable();
	App->disk->Enable();
	return ret;
}

Update_Status SceneLevel1::Update()
{
	spectators.Update();
	currentAnimation = &spectators;

	if (App->disk->saque == 0) {
		if (timer2 > 0) { timer2 -=1; }
		timer.Update();

		current_Timer_Animation = &timer;
	}

	if (App->disk->saque == 1)			//moure camera quan es fa gol
	{
		if (moureCameraGol == '1')
		{
			App->render->camera.x-=6;
			if (App->render->camera.x == -96)
				moureCameraGol = '2';
		}
		else
		{
			App->render->camera.x+=1;
			if (App->render->camera.x == -84)
				moureCameraGol = '1';
		}
	}
	else if (App->disk->saque == 2)		//moure camera quan es fa gol
	{
		if (moureCameraGol == '1')
		{
			App->render->camera.x+=6;
			if (App->render->camera.x == 96)
				moureCameraGol = '2';
		}
		else
		{
			App->render->camera.x-=1;
			if (App->render->camera.x == 84)
				moureCameraGol = '1';
		}
	}
	else
	{
		App->render->camera.x = 0;
		moureCameraGol = '1';
	}

	if (timerofpoints <= 0) {
		Points5ScoreR.Update();
	}

	/*char s[128];
	if (SDL_SCANCODE_H == SDL_KEYUP && points5right == 1)
	{
		for (int i = 0; i < NUM_POINTS; ++i)
		{
			sprintf_s(s, "Assets/UI/Points_Goal/3_points_goal_(right)/3_points_dreta_%d.png", i + 1);
			diskTexture[i] = App->textures->Load(s);
			App->render->Blit(diskTexture[i], 60, 60, NULL);
			if (i >= 17)
			{
				points5right = 0;
				App->textures->Load("Assets/UI/Points_Goal/3_points_goal_(right)/3_points_dreta_17.png");
			}
		}
	}*/

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, -27, 0, &(spectators.GetCurrentFrame()));
	App->render->Blit(bgExtremetopwall, 0, 16, NULL);
	App->render->Blit(bgExtremetopwallright, 267, 16, NULL);
	App->render->Blit(bgTopwall, 30, 20, NULL);
	App->render->Blit(bgObstacle, 144, 70, NULL);
	App->render->Blit(bgObstacle, 144, 166, NULL);
	App->render->Blit(bgNet, 142, 31, NULL);


	
		App->render->Blit(UI_Timer, 144, 13, &(timer.GetCurrentFrame()));


	

	if ((App->propsBackground->timersetcount < 190 && (App->disk->saque == 1 || App->disk->saque == 2||App->disk->saque == -1 || App->disk->saque == -2)) ) {

		switch (App->disk->sets) {
		 case 0:

			App->render->Blit(UI, 70, 86, &Set_1);
			   break;
			if (App->disk->timer_set > 0) {
		      case 1:

			App->render->Blit(UI, 70, 86, &Set_2);
			   break;
		 case 2:
			if (App->disk->sets_player1 == 1) {
				App->render->Blit(UI, 70, 86, &Set_Final);
			}
			   break;

			}
		}

	}
	
	if (App->disk->score_player_1 <= 13) {
		switch (App->disk->score_player_1) {

		case 0:
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 130, 17, &score0);
			break;
		case 2: 
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 130, 17, &score2);
			break;

		case 3:
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 131, 17, &score3);
			break;

		case 4: 
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 130, 17, &score4);
			break;

		case 5:
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 130, 17, &score5);
			break;

		case 6:
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 130, 17, &score6);
			break;

		case 7:
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 131, 17, &score7);
			break;

		case 8:
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 130, 17, &score8);
			break;

		case 9:
			App->render->Blit(UI, 114, 17, &score0);
			App->render->Blit(UI, 130, 17, &score9);
			break;

		case 10:
			App->render->Blit(UI, 124, 17, &score1);
			App->render->Blit(UI, 130, 17, &score0);
			break;

		case 11:
			App->render->Blit(UI, 124, 17, &score1);
			App->render->Blit(UI, 140, 17, &score1);
			break;

		case 12:
			App->render->Blit(UI, 124, 17, &score1);
			App->render->Blit(UI, 130, 17, &score2);
			break;

		case 13:
			App->render->Blit(UI, 124, 17, &score1);
			App->render->Blit(UI, 131, 17, &score3);
			break;


		}
	}

	if(App->disk->score_player_1 > 13) {

		App->render->Blit(UI, 124, 17, &score1);
		App->render->Blit(UI, 131, 17, &score3);

	}
	if (App->disk->score_player_2 <= 13) {
		switch (App->disk->score_player_2) {

		case 0:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 178, 17, &score0);
			break;
		case 2:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 178, 17, &score2);
			break;

		case 3:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 179, 17, &score3);
			break;

		case 4:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 178, 17, &score4);
			break;

		case 5:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 178, 17, &score5);
			break;

		case 6:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 178, 17, &score6);
			break;

		case 7:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 179, 17, &score7);
			break;

		case 8:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 178, 17, &score8);
			break;

		case 9:
			App->render->Blit(UI, 162, 17, &score0);
			App->render->Blit(UI, 178, 17, &score9);
			break;

		case 10:
			App->render->Blit(UI, 172, 17, &score1);
			App->render->Blit(UI, 178, 17, &score0);
			break;

		case 11:
			App->render->Blit(UI, 172, 17, &score1);
			App->render->Blit(UI, 188, 17, &score1);
			break;

		case 12:
			App->render->Blit(UI, 172, 17, &score1);
			App->render->Blit(UI, 178, 17, &score2);
			break;

		case 13:
			App->render->Blit(UI, 172, 17, &score1);
			App->render->Blit(UI, 179, 17, &score3);
			break;


		}
	}
	if (App->disk->score_player_2 > 13) {

		App->render->Blit(UI, 172, 17, &score1);
		App->render->Blit(UI, 179, 17, &score3);

	}

	if (App->disk->sets_player2 == 2 && App->disk->muerte_subita == false) {

		App->render->Blit(P2Win, 0, 0, NULL);
		App->render->Blit(UI, 30, 54, &P1LOSE);
		App->render->Blit(UI, 176, 48, &P2WIN);

		App->disk->si = 1;

	}
	if (App->disk->sets_player1 == 2 && App->disk->muerte_subita==false) {

		App->render->Blit(P1Win, 0, 0, NULL);
		App->render->Blit(UI, 18, 48, &P1WIN);
		App->render->Blit(UI, 175, 54, &P2LOSE);
		App->disk->si = 1;
	}

/*	if (App->disk->timer_set>0 && timersetcount > 190 && (App->disk->sets_player1 != 0 || App->disk->sets_player2 != 0)) {

		App->render->Blit(UI, 113, 124, &SetCount);

		if (App->disk->sets_player1 == 0) {
			App->render->Blit(UI, 50, 124, &SetScore0);
		}
		if (App->disk->sets_player1 == 1) {
			App->render->Blit(UI, 50, 124, &SetScore1);
		}
		if (App->disk->sets_player1 == 2) {
			App->render->Blit(UI, 50, 124, &SetScore2);
		}
		if (App->disk->sets_player2 == 0) {
			App->render->Blit(UI, 210, 124, &SetScore0);
		}
		if (App->disk->sets_player2 == 1) {
			App->render->Blit(UI, 210, 124, &SetScore1);
		}
		if (App->disk->sets_player2 == 2) {
			App->render->Blit(UI, 210, 124, &SetScore2);
		}


	}*/

	
	SDL_Rect P1WIN = {326, 86, 110, 32};

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->player2->Disable();
	
	App->disk->Disable();

	
	return true;
}