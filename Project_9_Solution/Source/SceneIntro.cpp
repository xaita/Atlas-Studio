#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/UI/Select Screens/SelectPlayerScene.png");
	
	UI = App->textures->Load("Assets/UI/UISpriteSheet_Upgrade.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	selectPlayer1 = '1';
	x1 = 8;
	y1 = 72;

	selectPlayer2 = '1';
	x2 = 24;
	y2 = 72;
	Readyp1 = false;
	Readyp2 = false;
	return ret;
}

Update_Status SceneIntro::Update()
{
	//seleccion player 1
	switch (selectPlayer1) {
	case '1':
		x1 = 8;
		y1 = 72;
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) 
			selectPlayer1 = '2';
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
			selectPlayer1 = '3';

		break;

	   case '2':
		x1 = 158;
		y1 = 72;
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) 
			selectPlayer1 = '1';
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) 
			selectPlayer1 = '3';
		
		break;

	case '3':
		x1 = 158;
		y1 = 184;
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) 
			selectPlayer1 = '1';
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) 
			selectPlayer1 = '2';

			break;
	}


	//if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && y1 != 50 + 100 && Readyp1 == false) {
	//	y1 += 56;
	//}
	//if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN && y1 != 50 && Readyp1 == false) {
	//	y1 -= 56;
	//}
	//if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN && x1 != 150 + 150 && Readyp1 == false) {
	//	x1 += 150;
	//}
	//if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN && x1 != 150 && Readyp1 == false) {
	//	x1 -= 150;
	//}


	//Player 2
	switch (selectPlayer2) {
	case '1':
		x2 = 32;
		y2 = 72;
		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN)
			selectPlayer2 = '2';
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN)
			selectPlayer2 = '3';

		break;

	case '2':
		x2 = 180;
		y2 = 72;
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
			selectPlayer2 = '1';
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN)
			selectPlayer2 = '3';

		break;

	case '3':
		x2 = 180;
		y2 = 184;
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
			selectPlayer2 = '1';
		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN)
			selectPlayer2 = '2';

		break;
	}

	if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {
		Readyp1 = true;
	}
	if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
		Readyp2 = true;
	}

	if (Readyp1 == true && Readyp2 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntroMapes, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(UI, x1, y1, &P1);
	App->render->Blit(UI, x2, y2, &P2);

	return Update_Status::UPDATE_CONTINUE;
}