#include "SceneWarning.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"

SceneWarning::SceneWarning(bool startEnabled) : Module(startEnabled)
{

}

SceneWarning::~SceneWarning()
{

}

// Load assets
bool SceneWarning::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/UI/Screens/Windjammers Mention.png");
	App->audio->PlayMusic("Assets/Audios/Music/Silence.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneWarning::Update()
{
	if (frame == 1) {
		App->fade->FadeToBlack(this, (Module*)App->sceneWindjammers, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntroSNK, 90);
	}

	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)
	{
		App->sceneLevel_1->Enable();
		Disable();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneWarning::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}