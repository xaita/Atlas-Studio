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

	bgTexture = App->textures->Load("Assets/UI/Screens/Japan vs Japan.png");
	/*select = App->textures->Load("Assets/UI/Select Screens/Purple rectangle.png");*/

	App->audio->PlayMusic("Assets/Audios/Music/01_Get Ready (Select Screen).ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneJapan::Update()
{
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
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(select, 164, 56, NULL); //rectangle de seleccionar stage

	return Update_Status::UPDATE_CONTINUE;
}