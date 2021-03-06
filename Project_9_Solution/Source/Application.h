#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 22

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModulePlayer2;
class ModuleDisk;
class SceneIntroSNK;
class SceneWarning;
class SceneWindjammers;
class SceneCoins;
class SceneLogo;
class SceneIntro;
class SceneIntroMapes;
class SceneVS;
class SceneLevel1;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class PropsBackground;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;
	ModulePlayer2* player2 = nullptr;
	ModuleDisk* disk = nullptr;

	SceneIntroSNK* sceneIntroSNK = nullptr;
	SceneWarning* sceneWarning = nullptr;
	SceneWindjammers* sceneWindjammers = nullptr;
	SceneCoins* sceneCoins = nullptr;
	SceneLogo* sceneLogo = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneIntroMapes* sceneIntroMapes = nullptr;
	SceneVS* sceneVS = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	PropsBackground* propsBackground = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__