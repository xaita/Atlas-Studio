#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleDisk.h"




SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Stages/Concrete/concrete-sprite-sheet.png");				//BG CONCRETE + PROPS
	bgTopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/top_wall.png");								//
	bgExtremetopwall = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall.png");				//
	bgExtremetopwallright = App->textures->Load("Assets/Sprites/Stages/Concrete/extreme_top_wall_Right.png");	//
	bgNet = App->textures->Load("Assets/Sprites/Stages/Concrete/net.png");										//

	//referee = App->textures->Load("Assets/Sprites/Referee/SpriteSheet_Arbi_Beach_Definitiu.png");				//ARBITRE
	//bgFrisbees = App->textures->Load("Assets/Sprites/Stages/Concrete/Neo Geo NGCD - Windjammers Flying Power Disc - Concrete.png");//discos del terra

	App->audio->PlayMusic("Assets/Audios/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", 1.0f);					//MUSICA

	spectators.PushBack({ 0,0,304,224 });																		//ANIMACIO ESPECTADORS
	spectators.PushBack({ 308,0,304,224 });
	spectators.PushBack({ 616,0,304,224 });
	spectators.loop = true;
	spectators.speed = 0.15f;

	//refereeAnim.PushBack({ 0,0,45,35 });																		//ANIMACIO ARBITRE
	


	//porteria esquerra
	App->collisions->AddCollider({ 7, 24, 4, 27 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 7, 166, 4, 27 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 7, 51, 4, 115 }, Collider::Type::SCOREZONE_2);

	//porteria dreta
	App->collisions->AddCollider({ 293, 24, 4, 27 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 293, 166, 4, 27 }, Collider::Type::SCOREZONE_1);
	App->collisions->AddCollider({ 293, 51, 4, 115 }, Collider::Type::SCOREZONE_2);

	

	App->player->Enable();
	App->enemies->Enable();
	App->player2->Enable();
	App->disk->Enable();
	return ret;
}

Update_Status SceneLevel1::Update()
{
	spectators.Update();
	currentAnimation = &spectators;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &(spectators.GetCurrentFrame()));
	App->render->Blit(bgExtremetopwall, 0, 16, NULL);
	App->render->Blit(bgExtremetopwallright, 267, 16, NULL);
	App->render->Blit(bgNet, 142, 31, NULL);
	App->render->Blit(bgTopwall, 30, 20, NULL);
	
	//App->render->Blit(referee, 138, 189, &(refereeAnim.GetCurrentFrame()));
	//App->render->Blit(bgFrisbees, 166, 209, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	App->disk->Disable();

	
	return true;
}