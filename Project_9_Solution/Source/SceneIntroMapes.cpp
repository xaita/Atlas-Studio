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

	bgTexture = App->textures->Load("Assets/UI/Select Screens/SelectMapScene.png");
	
	select = App->textures->Load("Assets/UI/Select Screens/Purple rectangle.png");

	beach = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Beach(name).png");
	concrete = App->textures->Load("Assets/UI\Maps_screenshots_and_titles/Concrete(name).png");
	lawn = App->textures->Load("Assets/UI/Maps_screenshots_and_titles/Lawn(name).png");

	
	X1 = 164;
	X2 = 164;
	Y1 = 56;
	Y2 = 56;
	Readym1 = false;
	Readym2 = false;


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntroMapes::Update()
{
	//player 1
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && Y1 != 56 + 46 && Readym1 == false) {
		Y1 += 23;
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN && Y1 != 56 && Readym1 == false) {
		Y1 -= 23;
	}
	

	//Player 2
	/*if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && Y2 != 150 && Ready2 == false) {
		Y2 += 50;
	}
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN && Y2 != 50 && Ready2 == false) {
		Y2 -= 50;
	}*/
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		Readym1 = true;
	}
	/*if (App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN) {
		Ready2 = true;
	}*/
	
	
	
	if (Readym1 == true /*&& Ready2 == true*/)
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
	App->render->Blit(beach, 200, 65, NULL);
	App->render->Blit(concrete, 192, 88, NULL);
	App->render->Blit(lawn, 201, 136, NULL);
	return Update_Status::UPDATE_CONTINUE;
}