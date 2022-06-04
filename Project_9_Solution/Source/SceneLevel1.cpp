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
	timerofpoints = 120;
	//moureCameraGol = '1';

	bgTexture = App->textures->Load("Assets/Sprites/Stages/Concrete/concrete-sprite-sheet.png");				//BG CONCRETE + PROPS
	bgTopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/top_wall.png");								//
	bgExtremetopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall.png");				//
	bgExtremetopwallright = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall_Right.png");
	bgObstacle = App->textures->Load("Assets/Sprites/Stages/Concrete/obstacle.png");	//
	bgNet = App->textures->Load("Assets/Sprites/Stages/Concrete/net.png");										//

	beachTexture = App->textures->Load("Assets/Sprites/Stages/Concrete/beachSpriteSheet.png");
	beachNet = App->textures->Load("Assets/Sprites/Stages/Concrete/anim901_0007_Red.png");

	UI = App->textures->Load("Assets/UI/UISpriteSheet_Upgrade.png");
	P1Win = App->textures->Load("Assets/UI/Others/P1Win.png");
	P2Win = App->textures->Load("Assets/UI/Others/P2Win.png");

	


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

	// 3 Esquerra
	Points3ScoreL.PushBack({ 441, 120, 63, 34 });
	Points3ScoreL.PushBack({ 112, 120, 59, 34 });
	Points3ScoreL.PushBack({ 171, 120, 55, 34 });
	Points3ScoreL.PushBack({ 226, 120, 51, 34 });
	Points3ScoreL.PushBack({ 277, 120, 47, 34 });
	Points3ScoreL.PushBack({ 324, 120, 43, 35 });
	Points3ScoreL.PushBack({ 367, 120, 39, 34 });
	Points3ScoreL.PushBack({ 406, 120, 35, 34 });
	Points3ScoreL.PushBack({ 0, 120, 28, 34 });
	Points3ScoreL.PushBack({ 28, 120, 24, 34 });
	Points3ScoreL.PushBack({ 52, 120, 20, 34 });
	Points3ScoreL.PushBack({ 72, 120, 16, 34 });
	Points3ScoreL.PushBack({ 88, 120, 12, 34 });
	Points3ScoreL.PushBack({ 100, 120, 8, 34 });
	Points3ScoreL.PushBack({ 108, 120, 4, 34 });
	Points3ScoreL.loop = false;
	Points3ScoreL.speed = 0.2;
	
	// 3 Dreta
	Points3ScoreR.PushBack({ 0, 188, 63, 34 });
	Points3ScoreR.PushBack({ 132, 154, 59, 34 });
	Points3ScoreR.PushBack({ 191, 154, 55, 34 });
	Points3ScoreR.PushBack({ 246, 154, 51, 34 });
	Points3ScoreR.PushBack({ 297, 154, 47, 34 });
	Points3ScoreR.PushBack({ 344, 154, 43, 34 });
	Points3ScoreR.PushBack({ 387, 154, 40, 34 });
	Points3ScoreR.PushBack({ 427, 154, 36, 34 });
	Points3ScoreR.PushBack({ 0, 154, 32, 34 });
	Points3ScoreR.PushBack({ 32, 154, 28, 34 });
	Points3ScoreR.PushBack({ 60, 154, 24, 34 });
	Points3ScoreR.PushBack({ 84, 154, 20, 34 });
	Points3ScoreR.PushBack({ 104, 154, 16, 34 });
	Points3ScoreR.PushBack({ 120, 154, 12, 34 });
	Points3ScoreR.loop = false;
	Points3ScoreR.speed = 0.2;

	// 5 Esquerra
	Points5ScoreR.PushBack({ 76, 258, 63, 35 });
	Points5ScoreR.PushBack({ 229, 223, 59, 35 });
	Points5ScoreR.PushBack({ 288, 223, 55, 35 });
	Points5ScoreR.PushBack({ 343, 223, 51, 35 });
	Points5ScoreR.PushBack({ 394, 223, 47, 35 });
	Points5ScoreR.PushBack({ 441, 223, 43, 35 });
	Points5ScoreR.PushBack({ 0, 258, 40, 35 });
	Points5ScoreR.PushBack({ 40, 258, 36, 35 });
	Points5ScoreR.PushBack({ 137, 223, 32, 35 });
	Points5ScoreR.PushBack({ 169, 223, 28, 35 });
	Points5ScoreR.PushBack({ 197, 223, 20, 35 });
	Points5ScoreR.PushBack({ 217, 223, 12, 35 });
	Points5ScoreR.loop = false;
	Points5ScoreR.speed = 0.2;

	// 5 Dreta
	Points5ScoreL.PushBack({ 74, 223, 63, 35 });
	Points5ScoreL.PushBack({ 230, 188, 59, 35 });
	Points5ScoreL.PushBack({ 289, 188, 55, 35 });
	Points5ScoreL.PushBack({ 344, 188, 51, 35 });
	Points5ScoreL.PushBack({ 395, 188, 47, 35 });
	Points5ScoreL.PushBack({ 442, 188, 43, 35 });
	Points5ScoreL.PushBack({ 0, 223, 39, 35 });
	Points5ScoreL.PushBack({ 39, 223, 35, 35 });
	Points5ScoreL.PushBack({ 99, 188, 31, 35 });
	Points5ScoreL.PushBack({ 130, 188, 28, 35 });
	Points5ScoreL.PushBack({ 158, 188, 24, 35 });
	Points5ScoreL.PushBack({ 182, 188, 20, 35 });
	Points5ScoreL.PushBack({ 202, 188, 16, 35 });
	Points5ScoreL.PushBack({ 218, 188, 12, 35 });
	Points5ScoreL.PushBack({ 62, 188, 9, 35 });
	Points5ScoreL.PushBack({ 71, 188, 5, 35 });
	Points5ScoreL.loop = false;
	Points5ScoreL.speed = 0.2;
	
	
	//porteria esquerra
	App->collisions->AddCollider({ 0, 26, 1, 24 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 0, 170, 1, 40 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 0, 66, 1, 89 }, Collider::Type::SCOREZONE_2);

	//porteria dreta
	App->collisions->AddCollider({ 300, 26, 1, 24 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 300, 170, 1, 40 }, Collider::Type::SCOREZONE_1);
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
	

	/*if (points5righttop == 1) {
		currentAnimationScore = &Points5ScoreR;
	}
	if (points5rightbot == 1) {
		currentAnimationScore = &Points5ScoreR;
		points5rightbot = 0;
	}
	if (points5lefttop == 1) {
		currentAnimationScore = &Points5ScoreL;
		points5lefttop = 0;
	}
	if (points5leftbot == 1) {
		currentAnimationScore = &Points5ScoreL;
		points5leftbot = 0;
	}*/



	if (App->disk->saque == 0 && App->disk->godmode == false) {
		if (timer2 > 0) { timer2 -=1; }
		timer.Update();

		current_Timer_Animation = &timer;
	}

	if (App->disk->saque == 1)			//moure camera quan es fa gol
	{
		//if (moureCameraGol == '1')
		//{
		//	App->render->camera.x-=6;
		//	if (App->render->camera.x == -96)
		//		moureCameraGol = '2';
		//}
		//else
		//{
		//	App->render->camera.x+=1;
		//	if (App->render->camera.x == -84)
		//		moureCameraGol = '1';
		//}

		if (App->render->camera.x > -96)
			App->render->camera.x -= 12;

	}
	else if (App->disk->saque == 2)		//moure camera quan es fa gol
	{
		//if (moureCameraGol == '1')
		//{
		//	App->render->camera.x+=6;
		//	if (App->render->camera.x == 96)
		//		moureCameraGol = '2';
		//}
		//else
		//{
		//	App->render->camera.x-=1;
		//	if (App->render->camera.x == 84)
		//		moureCameraGol = '1';
		//}
		if (App->render->camera.x < 96)
		App->render->camera.x += 12;
	}
	else
	{
		App->render->camera.x = 0;
		//moureCameraGol = '1';
	}



	if (timerofpoints > 0) {
		timerofpoints--;
	}
	if (timerofpoints == 0) {
		points5righttop = 0;
		points5rightbot = 0;
		points5lefttop = 0;
		points5leftbot = 0;
		points3left = 0;
		points3right = 0;
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
	Points5ScoreR.Update();
	Points5ScoreL.Update();
	Points3ScoreL.Update();
	Points3ScoreR.Update();

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
	

	if (points5righttop == 1) {
		
		App->render->Blit(UI, 250, 48, &(Points5ScoreR.GetCurrentFrame()));
		
	}
	if (points5rightbot == 1) {
		
		App->render->Blit(UI, 250, 192, &(Points5ScoreR.GetCurrentFrame()));
	}
	if (points5lefttop == 1) {
		
		App->render->Blit(UI, 30, 48, &(Points5ScoreL.GetCurrentFrame()));
	}
	if (points5leftbot == 1) {
		
		App->render->Blit(UI, 30, 192, &(Points5ScoreL.GetCurrentFrame()));
	}
	if (points3left == 1) {
		
		App->render->Blit(UI, 11, 90, &(Points3ScoreL.GetCurrentFrame()));
	}
	if (points3right == 1) {
		
		App->render->Blit(UI, 250, 90, &(Points3ScoreR.GetCurrentFrame()));
	}
	

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