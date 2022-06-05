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
	Coins = 0;

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
	bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits0.png");

	Coinfx = App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Others/InsertedCoin.wav");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneCoins::Update()
{
	char s[16];

	if (timer == 3) {
		if (frame < NUM_IMAGES - 1) {
			frame++;
			timer = 0;
		}
	}
	timer++;


	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{
		Coins++;
		if (Coins == 1)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits1.png");
		}
		if (Coins == 2)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits2.png");
		}
		if (Coins == 3)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits3.png");
		}
		if (Coins == 4)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits4.png");
		}
		if (Coins == 5)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits5.png");
		}
		if (Coins == 6)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits6.png");
		}
		if (Coins == 7)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits7.png");
		}
		if (Coins == 8)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits8.png");
		}
		if (Coins == 9)
		{
			bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits9.png");
		}
	}
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
	App->render->Blit(bgCredits, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}