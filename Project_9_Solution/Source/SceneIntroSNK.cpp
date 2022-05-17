#include <stdio.h>

#include "SceneIntroSNK.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "ModuleDisk.h"

SceneIntroSNK::SceneIntroSNK(bool startEnabled) : Module(startEnabled)
{
	
}

SceneIntroSNK::~SceneIntroSNK()
{

}

// Load assets
bool SceneIntroSNK::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	char s[128];

	for (int i = 1; i < 80; ++i)
	{
		sprintf_s(s, "Assets/UI/Screens/Neo Geo Intro/wjammers%d.png", i);
		bgTexture[i] = App->textures->Load(s);
	}
	frame = 0;
	App->audio->PlayMusic("Assets/Audios/Music/SNK Intro.ogg", 1.0f);

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

Update_Status SceneIntroSNK::Update()
{
	if (timer == 2) {
		frame++;
		timer = 0;
	}
	timer++;
	if (frame == 77) {
		App->fade->FadeToBlack(this, (Module*)App->sceneWindjammers, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneWindjammers, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntroSNK::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture[frame], 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}