#include "SceneJapan.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneJapan::SceneJapan(bool startEnabled) : Module(startEnabled)
{

}

SceneJapan::~SceneJapan()
{

}

// Load assets
bool SceneJapan::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgBlueTexture = App->textures->Load("Assets/UI/Screens/Blue texture.png");
	bgTexture = App->textures->Load("Assets/UI/Screens/Japan vs Japan.png");
	

	App->audio->PlayMusic("Assets/Audios/Music/01_Get Ready (Select Screen).ogg", 1.0f);

	background.PushBack({ 0,0,0,0 });
	background.PushBack({ 0,0,0,0 });
	background.loop = true;
	background.speed = 0.15f;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneJapan::Update()
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
Update_Status SceneJapan::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgBlueTexture, 0, 0, NULL);
	App->render->Blit(bgTexture, 0, 0, NULL);
	

	return Update_Status::UPDATE_CONTINUE;
}