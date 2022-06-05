#include "SceneVS.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneVS::SceneVS(bool startEnabled) : Module(startEnabled)
{

}

SceneVS::~SceneVS()
{

}

// Load assets
bool SceneVS::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgBlueTexture = App->textures->Load("Assets/UI/Screens/Scene Epi.png");
	bgTexture = App->textures->Load("Assets/UI/Screens/VS/Japan vs Japan.png");
	

	App->audio->PlayMusic("Assets/Audios/Music/02_Go for Broke! (Round Start).ogg", 1.0f);

	background.PushBack({ 0,0,304,224 });
	background.PushBack({ 305,0,304,224 });
	background.loop = true;
	background.speed = 0.4f;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneVS::Update()
{

	background.Update();
	currentAnimation = &background;



	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneVS::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgBlueTexture, 0, 0, &(background.GetCurrentFrame()));
	App->render->Blit(bgTexture, 0, 0, NULL);
	

	return Update_Status::UPDATE_CONTINUE;
}