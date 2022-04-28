#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleDisk.h"




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

	bgTexture = App->textures->Load("Assets/Sprites/Stages/Concrete/concrete-sprite-sheet.png");				//BG CONCRETE + PROPS
	bgTopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/top_wall.png");								//
	bgExtremetopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall.png");				//
	bgExtremetopwallright = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall_Right.png");	//
	bgNet = App->textures->Load("Assets/Sprites/Stages/Concrete/net.png");										//
	UI = App->textures->Load("Assets/UI/UISpriteSheet_Upgrade.png");
	P1Win = App->textures->Load("Assets/UI/Others/P1Win.png");
	P2Win = App->textures->Load("Assets/UI/Others/P2Win.png");




	UI_Timer = App->textures->Load("Assets/UI/timerSpriteSheet.png");

	

	App->audio->PlayMusic("Assets/Audios/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", 1.0f);					//MUSICA

	spectators.PushBack({ 0,0,304,224 });																		//ANIMACIO ESPECTADORS
	spectators.PushBack({ 308,0,304,224 });
	spectators.PushBack({ 616,0,304,224 });
	spectators.loop = true;
	spectators.speed = 0.15f;

	int x = 15;
	for (int i = 0; i < 32; i++) {
		timer.PushBack({ x,0,15,15 });
			x += 15;
	}
	timer.loop = false;
	timer.pingpong = false;
	timer.speed = 0.017f;
	
	current_Timer_Animation = &timer;


	//porteria esquerra
	App->collisions->AddCollider({ 7, 26, 4, 25 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 7, 168, 4, 25 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 7, 64, 4, 89 }, Collider::Type::SCOREZONE_2);

	//porteria dreta
	App->collisions->AddCollider({ 293, 26, 4, 25 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 293, 168, 4, 25 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 293, 64, 4, 89 }, Collider::Type::SCOREZONE_2);

	

	App->player->Enable();
	App->enemies->Enable();
	App->player2->Enable();
	App->disk->Enable();
	return ret;
}

Update_Status SceneLevel1::Update()
{
	spectators.Update();
	currentAnimation = &spectators;

	


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &(spectators.GetCurrentFrame()));
	App->render->Blit(bgExtremetopwall, 0, 16, NULL);
	App->render->Blit(bgExtremetopwallright, 267, 16, NULL);
	App->render->Blit(bgNet, 142, 31, NULL);
	App->render->Blit(bgTopwall, 30, 20, NULL);

	if (App->disk->arbitre == 0) {

		SDL_Rect rectTimer = current_Timer_Animation->GetCurrentFrame();
		App->render->Blit(UI_Timer, 144, 13, &rectTimer);


	}

	if (timersetcount > 190 && App->disk->sets_player1 != 0|| App->disk->sets_player2 != 0) {

			App->render->Blit(P2Win, 0, 0, NULL);
	}



	if ((timersetcount < 190 && (App->disk->saque == 1 || App->disk->saque == 2)) ) {

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

	if (App->disk->sets_player2 == 2) {

		App->render->Blit(P2Win, 0, 0, NULL);
		App->render->Blit(UI, 30, 54, &P1LOSE);
		App->render->Blit(UI, 176, 48, &P2WIN);



	}
	if (App->disk->sets_player1 == 2) {

		App->render->Blit(P1Win, 0, 0, NULL);
		App->render->Blit(UI, 18, 48, &P1WIN);
		App->render->Blit(UI, 175, 54, &P2LOSE);

	}
	

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	App->disk->Disable();

	
	return true;
}