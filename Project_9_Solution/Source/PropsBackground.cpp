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
	referee = App->textures->Load("Assets/Sprites/Referee/SpriteSheet_Arbi_Beach_Definitiu.png");				//ARBITRE
	bgFrisbees = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");//discos del terra

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	refereeIdle.PushBack({ 0,0,45,35 });																		//ANIMACIO ARBITRE
	refereeLookLeft.PushBack({ 0,102,44,34});
	refereeLookRight.PushBack({ 176,69,44,34 });

	refereePointLeft.PushBack({ 53, 35, 59, 31 });
	refereePointLeft.PushBack({ 112, 35, 48, 32 });
	refereePointLeft.PushBack({ 160, 35, 44, 28 });
	refereePointLeft.PushBack({ 204, 35, 45, 28 });
	refereePointLeft.speed = 0.1f;

	refereePointRight.PushBack({ 0, 69, 44, 27 });
	refereePointRight.PushBack({ 44, 69, 44, 28 });
	refereePointRight.PushBack({ 88, 69, 44, 32 });
	refereePointRight.PushBack({ 132, 69, 44, 31 });
	refereePointRight.speed = 0.1f;


	frisbees.PushBack({ 245,51,16,12 });

	return ret;
}

Update_Status PropsBackground::Update()
{
	if (App->disk->saque == 1) {
		currentAnimation = &refereePointRight;
	}

	else if (App->disk->saque == 2) {
		currentAnimation = &refereePointLeft;
	}

	else if (App->disk->position.x < 110) {
		//position.x += 2;
		currentAnimation = &refereeLookLeft;
	}

	else if (App->disk->position.x > 194) {
		currentAnimation = &refereeLookRight;
		//position.x += 2;
	}

	else {
		currentAnimation = &refereeIdle;
		//position.x -= 2;
	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status PropsBackground::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgGoal, 0, 22, NULL);
	App->render->Blit(bgGoalright, 266, 22, NULL);
	App->render->Blit(bgBotwall, 31, 202, NULL);
	App->render->Blit(bgFrisbees, 166, 209, &(frisbees.GetCurrentFrame()));
	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (currentAnimation == &refereePointLeft) {
		App->render->Blit(referee, 123, 189, &rect);
	}

	else
	App->render->Blit(referee, 138, 189, &rect);

	return Update_Status::UPDATE_CONTINUE;
}