#include "PropsBackground.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleDisk.h"

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

	bgBotwall = App->textures->Load("Assets/Sprites/Stages/Concrete/bot_wall.png");
	bgGoal = App->textures->Load("Assets/Sprites/Stages/Concrete/goal.png");
	bgGoalright = App->textures->Load("Assets/Sprites/Stages/Concrete/goalRight.png");
	bgGoalgoal = App->textures->Load("Assets/Sprites/Stages/Concrete/goal_supergoal.png");											//porteria quan es fa gol
	bgGoalgoalright = App->textures->Load("Assets/Sprites/Stages/Concrete/goal_supergoalRight.png");
	referee = App->textures->Load("Assets/Sprites/Referee/SpriteSheet_Arbi_Beach_Definitiu.png");									//ARBITRE
	bgFrisbees = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");//discos del terra
	UI = App->textures->Load("Assets/UI/UISpriteSheet_Upgrade.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	refereeIdle.PushBack({ 132, 210, 45,35 });																		//ANIMACIO ARBITRE
	refereeLookLeft.PushBack({ 0,105,44,35});
	refereeLookRight.PushBack({ 176,70,44,35 });

	refereePointLeft.PushBack({ 53, 36, 59, 35 });
	refereePointLeft.PushBack({ 112, 36, 48, 35 });
	refereePointLeft.PushBack({ 160, 36, 44, 35 });
	refereePointLeft.PushBack({ 204, 36, 45, 35 });
	refereePointLeft.speed = 0.1f;
	refereePointLeft.loop = true;

	refereePointRight.PushBack({ 0, 70, 44, 35 });
	refereePointRight.PushBack({ 44, 70, 44, 35 });
	refereePointRight.PushBack({ 88, 70, 44, 35 });
	refereePointRight.PushBack({ 132, 70, 44, 35 });
	refereePointRight.speed = 0.1f;
	refereePointRight.loop = true;


	frisbees.PushBack({ 245,51,16,12 });

	return ret;
}

Update_Status PropsBackground::Update()
{
	--timerrefree;
	
	if (App->disk->saque == 1) {
		currentAnimation = &refereePointRight;//NO FUNCIONA canvia l'sprite pero no fa l'animacio
		timerrefree = 20;
	}

	else if (App->disk->saque == 2) {
		currentAnimation = &refereePointLeft;
		timerrefree = 20;
	}

	else if (App->disk->position.x < 110) {
		currentAnimation = &refereeLookLeft;
	}

	else if (App->disk->position.x > 194) {
		currentAnimation = &refereeLookRight;
	}

	else if (timerrefree <= 0){
		currentAnimation = &refereeIdle;
	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status PropsBackground::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgBotwall, 31, 202, NULL);
	App->render->Blit(bgFrisbees, 166, 209, &(frisbees.GetCurrentFrame()));

	if (App->disk->saque == 1) {
		App->render->Blit(bgGoalgoal, -15, 22, NULL);
	}
	else
		App->render->Blit(bgGoal, 0, 22, NULL);

	if (App->disk->saque == 2) {
		App->render->Blit(bgGoalgoalright, 266, 22, NULL);
	}
	else
		App->render->Blit(bgGoalright, 266, 22, NULL);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (currentAnimation == &refereePointLeft) {
		App->render->Blit(referee, 123, 190, &rect);//////////////////////////////arreglo de l'animacio de l'arbitre que sortia desplaçada
	}

	else
	App->render->Blit(referee, 138, 189, &rect);

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