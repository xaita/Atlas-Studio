#include "SceneIntroMapes.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneCoins.h"


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

	bgTexture = App->textures->Load("Assets/UI/Select Screens/SelectMapScene.png");
	
	select = App->textures->Load("Assets/UI/Select Screens/Purple rectangle.png");

	App->audio->LoadFx("Assets/Audios/SFX and Voice lines/Others/Select.wav");

	beachname = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Beach(name).png");
	concretename = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Concrete(name).png");
	lawnname = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Lawn(name).png");

	beachimg = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Beach.png");
	concreteimg = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Concrete.png");
	lawnimg = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Lawn.png");

	selectMap = '1';

	X1 = 164;
	Y1 = 56;
	Readym1 = false;
	Readym2 = false;

	App->sceneCoins->Coins;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntroMapes::Update()
{
	//player 1
	switch (selectMap) {
	case '1':
		Y1 = 56;
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) {
			App->audio->PlayFx(selectm, 0);
			selectMap = '3';
		}
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) {
			App->audio->PlayFx(selectm, 0);
			selectMap = '2';
		}

		break;

	case '2':
		Y1 = 80;
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) {
			App->audio->PlayFx(selectm, 0);
			selectMap = '1';
		}
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) {
			App->audio->PlayFx(selectm, 0);
			selectMap = '3';
		}

		break;

	case '3':
		Y1 = 128;
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) {
			App->audio->PlayFx(selectm, 0);
			selectMap = '2';
		}
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) {
			App->audio->PlayFx(selectm, 0);
			selectMap = '1';
		}

		break;
	}
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN || App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
		Readym1 = true;
	}
	/*if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
		Ready2 = true;
	}*/
	
	
	
	if (Readym1 == true /*&& Ready2 == true*/)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneJapan, 90);
	}

	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{
		App->sceneCoins->Coins++;
	}
	if (App->sceneCoins->Coins == 1)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits1.png");
	}
	if (App->sceneCoins->Coins == 2)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits2.png");
	}
	if (App->sceneCoins->Coins == 3)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits3.png");
	}
	if (App->sceneCoins->Coins == 4)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits4.png");
	}
	if (App->sceneCoins->Coins == 5)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits5.png");
	}
	if (App->sceneCoins->Coins == 6)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits6.png");
	}
	if (App->sceneCoins->Coins == 7)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits7.png");
	}
	if (App->sceneCoins->Coins == 8)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits8.png");
	}
	if (App->sceneCoins->Coins == 9)
	{
		bgCredits = App->textures->Load("Assets/UI/Screens/Credits/Credits9.png");
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntroMapes::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(select, X1, Y1, NULL); //rectangle de seleccionar stage
	App->render->Blit(beachname, 200, 65, NULL);
	App->render->Blit(concretename, 192, 89, NULL);
	App->render->Blit(lawnname, 208, 137, NULL);
	App->render->Blit(bgCredits, 0, 0, NULL);
	if(selectMap=='1')
		App->render->Blit(beachimg, 24, 84, NULL);
	else if(selectMap=='2')
		App->render->Blit(concreteimg, 24, 84, NULL);
	else if(selectMap=='3')
		App->render->Blit(lawnimg, 24, 84, NULL);
	return Update_Status::UPDATE_CONTINUE;
}