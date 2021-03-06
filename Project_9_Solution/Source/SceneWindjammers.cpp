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

	for (int i = 0; i < NUM_IMAGES; ++i)
	{
		sprintf_s(s, "Assets/UI/Screens/Windjammers Intro/wjammers%d.png", i+1);
		bgTexture[i] = App->textures->Load(s);
		if (i == 63)
		{
			sprintf_s(s, "Assets/UI/Screens/Windjammers Intro/wjammers63.png");
			bgTexture[i] = App->textures->Load(s);
		}
	}
	frame = 0;
	timer = 0;
	App->audio->PlayMusic("Assets/Audios/Music/01_Get Ready (Select Screen).ogg", 1.0f);
	
	Coinfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Others/InsertedCoin.wav");




	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneWindjammers::Update()
{
	if (timer == 2) {
		if (frame < NUM_IMAGES - 1) {
			frame++;
			timer = 0;
		}
	}
	timer++;


	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneCoins, 90);
		App->audio->PlayFx(Coinfx, 0);
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