#include "SceneIntroMapes.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntroMapes::SceneIntroMapes(bool startEnabled) : Module(startEnabled)
{

}

SceneIntroMapes::~SceneIntroMapes()
{

}

// Load assets
bool SceneIntroMapes::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/UI/Select Screens/Map Screen.png");
	/*select = App->textures->Load("Assets/UI/Select Screens/Purple rectangle.png");*/

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntroMapes::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneJapan, 90);
	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntroMapes::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(select, 164, 56, NULL); //rectangle de seleccionar stage

	return Update_Status::UPDATE_CONTINUE;
}