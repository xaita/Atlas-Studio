#include <stdio.h>

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
	char s[128];

	for (int i = 0; i < NUM_IMAGES; ++i)
	{
		sprintf_s(s, "Assets/UI/Screens/Warning/Warning%d.png", i + 1);
		bgTexture[i] = App->textures->Load(s);
	}
	frame = 0;
	timer = 0;

	
	App->audio->PlayMusic("Assets/Audios/Music/Silence.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneWarning::Update()
{
	if (timer == 12) {
		if (frame < NUM_IMAGES - 1) {
			frame++;
			timer = 0;
		}
	}
	timer++;

	if (frame == 14) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntroSNK, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntroSNK, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneWarning::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture[frame], 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}