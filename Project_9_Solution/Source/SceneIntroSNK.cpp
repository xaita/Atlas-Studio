#include "SceneIntroSNK.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include"SceneLevel1.h"
#include"ModuleDisk.h"

SceneIntroSNK::SceneIntroSNK(bool startEnabled) : Module(startEnabled)
{
	/*SNK.PushBack({ 0,0,304,224 });
	SNK.PushBack({ 0,305,304,224 });
	SNK.PushBack({ 0,609,304,224 });
	SNK.PushBack({ 0,913,304,224 });
	SNK.PushBack({ 225,0,304,224 });
	SNK.PushBack({ 225,305,304,224 });
	SNK.PushBack({ 225,609,304,224 });
	SNK.PushBack({ 225,913,304,224 });
	SNK.PushBack({ 449,0,304,224 });
	SNK.PushBack({ 449,305,304,224 });
	SNK.PushBack({ 449,609,304,224 });
	SNK.PushBack({ 449,913,304,224 });
	SNK.PushBack({ 673,0,304,224 });
	SNK.PushBack({ 673,305,304,224 });
	SNK.PushBack({ 673,609,304,224 });
	SNK.PushBack({ 673,913,304,224 });
	SNK.PushBack({ 897,0,304,224 });
	SNK.PushBack({ 897,305,304,224 });
	SNK.PushBack({ 897,609,304,224 });
	SNK.PushBack({ 897,913,304,224 });
	SNK.PushBack({ 1121,0,304,224 });
	SNK.PushBack({ 1121,305,304,224 });
	SNK.PushBack({ 1121,609,304,224 });
	SNK.PushBack({ 1121,913,304,224 });
	SNK.PushBack({ 1345,0,304,224 });
	SNK.PushBack({ 1345,305,304,224 });
	SNK.PushBack({ 1345,609,304,224 });
	SNK.PushBack({ 1345,913,304,224 });
	SNK.PushBack({ 1569,0,304,224 });
	SNK.PushBack({ 1569,305,304,224 });
	SNK.PushBack({ 1569,609,304,224 });
	SNK.PushBack({ 1569,913,304,224 });
	SNK.PushBack({ 1793,0,304,224 });
	SNK.PushBack({ 1793,305,304,224 });
	SNK.PushBack({ 1793,609,304,224 });
	SNK.PushBack({ 1793,913,304,224 });
	SNK.PushBack({ 2017,0,304,224 });
	SNK.PushBack({ 2017,305,304,224 });
	SNK.PushBack({ 2017,609,304,224 });
	SNK.PushBack({ 2017,913,304,224 });
	SNK.PushBack({ 2241,0,304,224 });
	SNK.PushBack({ 2241,305,304,224 });
	SNK.PushBack({ 2241,609,304,224 });
	SNK.PushBack({ 2241,913,304,224 });
	SNK.PushBack({ 2465,0,304,224 });
	SNK.PushBack({ 2465,305,304,224 });
	SNK.PushBack({ 2465,609,304,224 });
	SNK.PushBack({ 2465,0,304,224 });
	SNK.PushBack({ 2689,0,304,224 });
	SNK.PushBack({ 2689,305,304,224 });
	SNK.PushBack({ 2689,609,304,224 });
	SNK.PushBack({ 2689,913,304,224 });
	SNK.PushBack({ 2913,0,304,224 });
	SNK.PushBack({ 2913,305,304,224 });
	SNK.PushBack({ 2913,609,304,224 });
	SNK.PushBack({ 2913,913,304,224 });
	SNK.PushBack({ 3137,0,304,224 });
	SNK.PushBack({ 3137,305,304,224 });
	SNK.PushBack({ 3137,609,304,224 });
	SNK.PushBack({ 3137,913,304,224 });
	SNK.PushBack({ 3361,0,304,224 });
	SNK.PushBack({ 3361,305,304,224 });
	SNK.PushBack({ 3361,609,304,224 });
	SNK.PushBack({ 3361,913,304,224 });
	SNK.PushBack({ 3585,0,304,224 });
	SNK.PushBack({ 3585,305,304,224 });
	SNK.PushBack({ 3585,609,304,224 });
	SNK.PushBack({ 3585,913,304,224 });
	SNK.PushBack({ 3809,0,304,224 });
	SNK.PushBack({ 3809,305,304,224 });
	SNK.PushBack({ 3809,609,304,224 });
	SNK.PushBack({ 3809,913,304,224 });
	SNK.PushBack({ 4033,0,304,224 });
	SNK.PushBack({ 4033,305,304,224 });
	SNK.PushBack({ 4033,609,304,224 });
	SNK.PushBack({ 4033,913,304,224 });
	SNK.PushBack({ 4257,0,304,224 });
	SNK.PushBack({ 4257,305,304,224 });
	SNK.PushBack({ 4257,609,304,224 });

	SNK.speed = 0.4f;*/
}

SceneIntroSNK::~SceneIntroSNK()
{

}

// Load assets
bool SceneIntroSNK::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/UI/Screens/SNKIntro.png");
	App->audio->PlayMusic("Assets/Audios/Music/SNK Intro.ogg", 1.0f);

	/*currentAnimation = &SNK;*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

Update_Status SceneIntroSNK::Update()
{

	/*SNK.Update();*/

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneWindjammers, 90);
	}

	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)
	{
		App->sceneLevel_1->Enable();
		Disable();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntroSNK::PostUpdate()
{
	// Draw everything --------------------------------------
	/*App->render->Blit(bgSNK, 0, 0, &(SNK.GetCurrentFrame()));*/
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}