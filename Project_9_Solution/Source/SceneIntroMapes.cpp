#include "SceneIntroMapes.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

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

	bgTexture = App->textures->Load("Assets/UI/Select Screens/Map Screen.png");
	
	select = App->textures->Load("Assets/UI/Select Screens/Purple rectangle.png");

	
	X1 = 164;
	X2 = 164;
	Y1 = 56;
	Y2 = 56;
	Ready1 = false;
	Ready2 = false;


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntroMapes::Update()
{
	//player 1
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && X1 != 150 && Ready1 == false) {
		Y1 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN && X1 != 50 && Ready1 == false) {
		Y1 -= 50;
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN && X1 != 100 && Ready1 == false) {
		X1 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN && X1 != 50 && Ready1 == false) {
		X1 -= 50;
	}

	//Player 2
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && X1 != 150 && Ready2 == false) {
		Y1 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN && X1 != 50 && Ready2 == false) {
		Y1 -= 50;
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN && X1 != 100 && Ready2 == false) {
		X1 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN && X1 != 50 && Ready2 == false) {
		X1 -= 50;
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		Ready1 = true;
	}
	if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
		Ready2 = true;
	}
	
	
	
	if (Ready1 == true && Ready2 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneJapan, 90);
	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntroMapes::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(select, X1, Y1, NULL); //rectangle de seleccionar stage

	return Update_Status::UPDATE_CONTINUE;
}