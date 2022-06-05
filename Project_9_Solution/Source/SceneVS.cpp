#include "SceneVS.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"

SceneVS::SceneVS(bool startEnabled) : Module(startEnabled)
{

}

SceneVS::~SceneVS()
{

}

// Load assets
bool SceneVS::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgBlueTexture = App->textures->Load("Assets/UI/Screens/Scene Epi.png");
	

	App->audio->PlayMusic("Assets/Audios/Music/02_Go for Broke! (Round Start).ogg", 1.0f);

	background.PushBack({ 0,0,304,224 });
	background.PushBack({ 305,0,304,224 });
	background.loop = true;
	background.speed = 0.4f;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneVS::Update()
{

	background.Update();
	currentAnimation = &background;


	if (App->sceneIntro->xdselectPlayer1 == '1' && App->sceneIntro->xdselectPlayer2 == '1')
	{
			bgTexture = App->textures->Load("Assets/UI/Screens/VS/Japan vs Japan.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '1' && App->sceneIntro->xdselectPlayer2 == '2')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Japan vs Korea.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '1' && App->sceneIntro->xdselectPlayer2 == '3')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Japan vs Germany.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '2' && App->sceneIntro->xdselectPlayer2 == '1')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Korea vs Japan.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '2' && App->sceneIntro->xdselectPlayer2 == '2')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Korea vs Korean.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '3' && App->sceneIntro->xdselectPlayer2 == '1')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Germany vs Japan.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '2' && App->sceneIntro->xdselectPlayer2 == '3')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Korea vs Germany.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '3' && App->sceneIntro->xdselectPlayer2 == '2')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Germany vs Korea.png");
	}
	if (App->sceneIntro->xdselectPlayer1 == '3' && App->sceneIntro->xdselectPlayer2 == '3')
	{
		bgTexture = App->textures->Load("Assets/UI/Screens/VS/Germany vs Germany.png");
	}

	

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneVS::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgBlueTexture, 0, 0, &(background.GetCurrentFrame()));
	App->render->Blit(bgTexture, 0, 0, NULL);
	

	return Update_Status::UPDATE_CONTINUE;
}