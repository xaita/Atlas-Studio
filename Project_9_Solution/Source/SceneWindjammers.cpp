#include <stdio.h>

#include "SceneWindjammers.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneWindjammers::SceneWindjammers(bool startEnabled) : Module(startEnabled)
{

}

SceneWindjammers::~SceneWindjammers()
{

}

// Load assets
bool SceneWindjammers::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	char s[128];

	for (int i = 0; i < 76; ++i)
	{
		sprintf_s(s, "Assets/UI/Screens/Windjammers Intro/wjammers%d.png", i);
		bgTexture[i] = App->textures->Load(s);
	}
	frame = 0;
	App->audio->PlayMusic("Assets/Audios/Music/01_Get Ready (Select Screen).ogg", 1.0f);
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneWindjammers::Update()
{
	if (timer == 3) {
		frame++;
		timer = 0;
	}
	timer++;
	if (frame == 75) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneWindjammers::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture[frame], 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}