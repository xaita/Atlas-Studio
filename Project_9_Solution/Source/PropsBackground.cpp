#include "PropsBackground.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Animation.h"

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

	refereeAnim.PushBack({ 0,0,45,35 });																		//ANIMACIO ARBITRE
	frisbees.PushBack({ 245,51,16,12 });

	return ret;
}

Update_Status PropsBackground::Update()
{
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
	App->render->Blit(referee, 138, 189, &(refereeAnim.GetCurrentFrame()));

	return Update_Status::UPDATE_CONTINUE;
}