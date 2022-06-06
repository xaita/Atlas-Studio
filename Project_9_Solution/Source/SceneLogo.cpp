#include <stdio.h>

#include "SceneLogo.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "ModuleDisk.h"
#include "SceneIntro.h"
#include "SceneIntroMapes.h"

SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{

}

SceneLogo::~SceneLogo()
{

}

// Load assets
bool SceneLogo::Start()
{

	LOG("Loading background assets");

	bool ret = true;
	
	bgTexture = App->textures->Load("Assets/UI/Screens/Atlas Logo/LogoAtlas0.png");
	atlas = App->audio->LoadFx("Assets/Audios/Music/Among Us Impostor Sound Effect.ogg");
	App->audio->PlayFx(atlas, 0);
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneLogo::Update()
{
	


	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneWarning, 90);
	}


	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)
	{

		App->sceneIntro->Enable();
		Disable();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLogo::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}