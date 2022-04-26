#include "NeoGeoIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

NeoGeoIntro::NeoGeoIntro(bool startEnabled) : Module(startEnabled)
{

}

NeoGeoIntro::~NeoGeoIntro()
{

}

// Load assets
bool NeoGeoIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/UI/Other Screens/NeoGeoScreen.png");
	App->audio->PlayMusic("Assets/Audios/Music/SNK_Intro.ogg", 0.5f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status NeoGeoIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status NeoGeoIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}