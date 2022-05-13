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

	bgTexture = App->textures->Load("Assets/UI/Select Screens/SelectPlayer.png");
	App->audio->PlayMusic("Assets/Audios/Music/01_Get Ready (Select Screen).ogg", 1.0f);
	UI = App->textures->Load("Assets/UI/UISpriteSheet_Upgrade.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	x1 = 50;
	y1 = 50;
	x2 = 50;
	y2 = 50;
	Readyp1 = false;
	Readyp2 = false;
	return ret;
}

Update_Status SceneIntro::Update()
{
	//player 1
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && y1 != 50 + 100 && Readyp1 == false) {
		y1 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN && y1 != 50 && Readyp1 == false) {
		y1 -= 50;
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN && x1 != 50 + 50 && Readyp1 == false) {
		x1 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN && x1 != 50 && Readyp1 == false) {
		x1 -= 50;
	}


	//Player 2
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && y2 != 150 && Readyp2 == false) {
		y2 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN && y2 != 50 && Readyp2 == false) {
		y2 -= 50;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
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

	return Update_Status::UPDATE_CONTINUE;
}