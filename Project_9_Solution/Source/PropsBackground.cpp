#include "PropsBackground.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

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

	App->render->camera.x = 0;
	App->render->camera.y = 0;

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

	return Update_Status::UPDATE_CONTINUE;
}