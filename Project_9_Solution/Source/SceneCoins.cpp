#include <stdio.h>

#include "SceneCoins.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneCoins::SceneCoins(bool startEnabled) : Module(startEnabled)
{

}

SceneCoins::~SceneCoins()
{

}

// Load assets
bool SceneCoins::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	char s[64];

	for (int i = 0; i < NUM_IMAGES; ++i)
	{
		sprintf_s(s, "Assets/UI/Screens/Scene Coins/wjammers%d.png", i + 1);
		bgTexture[i] = App->textures->Load(s);
		if (i == 41)
		{
			sprintf_s(s, "Assets/UI/Screens/Scene Coins/wjammers41.png");
			bgTexture[i] = App->textures->Load(s);
		}
	}
	frame = 0;
	timer = 0;
	App->audio->PlayMusic("Assets/Audios/Music/01_Get Ready (Select Screen).ogg", 1.0f);

	bgYellow = App->textures->Load("Assets/UI/Screens/YellowUI.png");
	bgCredit = App->textures->Load("Assets/UI/Screens/Credits.png");

	Coinfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Others/InsertedCoin.wav");



	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{

	}


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneCoins::Update()
{
	if (timer == 3) {
		if (frame < NUM_IMAGES - 1) {
			frame++;
			timer = 0;
		}
	}
	timer++;



	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{
		App->audio->PlayFx(Coinfx, 0);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneCoins::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture[frame], 0, 0, NULL);
	App->render->Blit(bgYellow, 0, 0, NULL);
	App->render->Blit(bgCredit, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}