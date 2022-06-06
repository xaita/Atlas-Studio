#include "PropsBackground.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleDisk.h"
#include "SceneIntroMapes.h"

PropsBackground::PropsBackground(bool startEnabled) : Module(startEnabled)
{

}

PropsBackground::~PropsBackground()
{

}

// Load assets
bool PropsBackground::Start()
{
	LOG("Loading background props");

	bool ret = true;

	//beach
	beachBotWall = App->textures->Load("Assets/Sprites/Stages/Beach/botWall.png");
	//beachTopWall = App->textures->Load("Assets/Sprites/Stages/Beach/topWall.png");
	beachLeftGoal = App->textures->Load("Assets/Sprites/Stages/Beach/porteriaEsquerra.png");
	beachRightGoal = App->textures->Load("Assets/Sprites/Stages/Beach/porteriaDreta.png");
	//beachGoalGoal = App->textures->Load("Assets/Sprites/Stages/Beach/.png"); falta sprite


	//concrete
	bgBotwall = App->textures->Load("Assets/Sprites/Stages/Concrete/bot_wall.png");
	bgGoal = App->textures->Load("Assets/Sprites/Stages/Concrete/goal.png");
	bgGoalright = App->textures->Load("Assets/Sprites/Stages/Concrete/goalRight.png");
	bgGoalgoal = App->textures->Load("Assets/Sprites/Stages/Concrete/goal_supergoal.png");											//porteria quan es fa gol
	bgGoalgoalright = App->textures->Load("Assets/Sprites/Stages/Concrete/goal_supergoalRight.png");

	//lawn
	lawnBotWall = App->textures->Load("Assets/Sprites/Stages/Lawn/botWall.png");
	lawnTopWall = App->textures->Load("Assets/Sprites/Stages/Lawn/topWall.png");
	lawnLeftGoal = App->textures->Load("Assets/Sprites/Stages/Lawn/porteriaEsquerra.png");
	lawnRightGoal = App->textures->Load("Assets/Sprites/Stages/Lawn/porteriaDreta.png");
	lawnLeftGoalGoal = App->textures->Load("Assets/Sprites/Stages/Lawn/porteriaGolEsquerra.png");
	lawnRightGoalGoal = App->textures->Load("Assets/Sprites/Stages/Lawn/porteriaGolDreta.png");

	//ARBITRE
	referee = App->textures->Load("Assets/Sprites/Referee/SpriteSheet_Arbi_Beach_Definitiu.png");									
	bgFrisbees = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");//discos del terra
	UI = App->textures->Load("Assets/UI/UISpriteSheet_Upgrade.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	refereeIdle.PushBack({ 177, 210, 59,35 });																		//ANIMACIO ARBITRE
	refereeLookLeft.PushBack({ 0,105,59,35});
	refereeLookRight.PushBack({ 236,70,59,35 });

	refereePointLeft.PushBack({ 236, 36, 59, 35 });
	refereePointLeft.PushBack({ 177, 36, 59, 35 });
	refereePointLeft.PushBack({ 118, 36, 59, 35 });
	refereePointLeft.PushBack({ 59, 36, 59, 35 });
	refereePointLeft.PushBack({ 59, 36, 59, 35 });
	refereePointLeft.PushBack({ 59, 36, 59, 35 });
	refereePointLeft.PushBack({ 59, 36, 59, 35 });
	refereePointLeft.PushBack({ 59, 36, 59, 35 });
	refereePointLeft.PushBack({ 59, 36, 59, 35 });
	refereePointLeft.PushBack({ 59, 36, 59, 35 });
	refereePointLeft.PushBack({ 118, 36, 59, 35 });
	refereePointLeft.PushBack({ 177, 36, 59, 35 });
	refereePointLeft.PushBack({ 236, 36, 59, 35 });
	refereePointLeft.speed = 0.1f;
	refereePointLeft.loop = false;

	refereePointRight.PushBack({ 177, 70, 59, 35 });
	refereePointRight.PushBack({ 118, 70, 59, 35 });
	refereePointRight.PushBack({ 59, 70, 59, 35 });
	refereePointRight.PushBack({ 0, 70, 59, 35 });
	refereePointRight.PushBack({ 0, 70, 59, 35 });
	refereePointRight.PushBack({ 0, 70, 59, 35 });
	refereePointRight.PushBack({ 0, 70, 59, 35 });
	refereePointRight.PushBack({ 0, 70, 59, 35 });
	refereePointRight.PushBack({ 0, 70, 59, 35 });
	refereePointRight.PushBack({ 0, 70, 59, 35 });
	refereePointRight.PushBack({ 59, 70, 59, 35 });
	refereePointRight.PushBack({ 118, 70, 59, 35 });
	refereePointRight.PushBack({ 177, 70, 59, 35 });
	refereePointRight.speed = 0.1f;
	refereePointRight.loop = false;

	refereeNewDisk.PushBack({ 118,210,59,35 });
	refereeNewDisk.PushBack({ 59,210,59,35 });
	refereeNewDisk.PushBack({ 0,210,59,35 });
	refereeNewDisk.PushBack({ 236,175,59,35 });
	refereeNewDisk.PushBack({ 177,175,59,35 });
	refereeNewDisk.PushBack({ 118,175,59,35 });
	refereeNewDisk.PushBack({ 59,175,59,35 });
	refereeNewDisk.PushBack({ 0,175,59,35 });
	refereeNewDisk.PushBack({ 236,175,59,35 });
	refereeNewDisk.PushBack({ 177,175,59,35 });
	refereeNewDisk.speed = 0.2f;
	refereeNewDisk.loop = false;

	frisbees.PushBack({ 245,51,16,12 });


	return ret;
}

Update_Status PropsBackground::Update()
{
	--timerrefree;

	
	if (App->disk->saque == 1) {
		currentAnimationReferee = &refereePointRight;//NO FUNCIONA canvia l'sprite pero no fa l'animacio
		timerrefree = 40;
	}

	else if (App->disk->saque == 2) {
		currentAnimationReferee = &refereePointLeft;
		timerrefree = 40;
	}

	else if (App->disk->position.x < 110) {
		currentAnimationReferee = &refereeLookLeft;
	}

	else if (App->disk->position.x > 194) {
		currentAnimationReferee = &refereeLookRight;
	}


	else if (timerrefree <= 0){
		currentAnimationReferee = &refereeIdle;
		refereePointRight.Reset();
		refereePointLeft.Reset();
	}
	else if (timerrefree <= 20) {
		currentAnimationReferee = &refereeNewDisk;
	}
	currentAnimationReferee->Update();
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status PropsBackground::PostUpdate()
{
	// Draw everything --------------------------------------
	if (App->sceneIntroMapes->Readymap == true) {
		switch (App->sceneIntroMapes->selectMap) {
		case '1':
			if (App->disk->saque == 1)
				App->render->Blit(beachLeftGoalGoal, 0, 0, NULL);
			else
				App->render->Blit(beachLeftGoal, 0, 0, NULL);
			if (App->disk->saque == 2)
				App->render->Blit(beachRightGoalGoal, 0, 0, NULL);
			else
				App->render->Blit(beachRightGoal, 0, 0, NULL);
			App->render->Blit(beachBotWall, 0, 0, NULL);
			break;
		case'2':
			if (App->disk->saque == 1)
				App->render->Blit(bgGoalgoal, -15, 22, NULL);
			else
				App->render->Blit(bgGoal, 0, 22, NULL);
			if (App->disk->saque == 2)
				App->render->Blit(bgGoalgoalright, 266, 22, NULL);
			else
				App->render->Blit(bgGoalright, 266, 22, NULL);
			App->render->Blit(bgBotwall, 31, 202, NULL);
			break;
		case '3':
			if (App->disk->saque == 1)
				App->render->Blit(lawnLeftGoalGoal, -15, 22, NULL);
			else
				App->render->Blit(lawnLeftGoal, -9, 20, NULL);
			if (App->disk->saque == 2)
				App->render->Blit(lawnRightGoalGoal, 266, 22, NULL);
			else
				App->render->Blit(lawnRightGoal, 266, 22, NULL);
			App->render->Blit(lawnBotWall, 31, 202, NULL);
			break;
		}
	}
	App->render->Blit(bgFrisbees, 166, 209, &(frisbees.GetCurrentFrame()));


	SDL_Rect rect = currentAnimationReferee->GetCurrentFrame();

	App->render->Blit(referee, 123, 189, &rect);

	if (App->disk->timer_set > 0 && timersetcount > 190 && (App->disk->sets_player1 != 0 || App->disk->sets_player2 != 0)) {

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


	}

	return Update_Status::UPDATE_CONTINUE;
}