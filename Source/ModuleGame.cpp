#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"


ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background_normal = LoadTexture("Assets/sky.png");
	background_dawn = LoadTexture("Assets/sky_dawn.png");

	return ret;
}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		drawDawnSky = !drawDawnSky;
	}

	if (!drawDawnSky)
	{
		App->renderer->Draw(background_normal, 0, 0);
	}
	else
	{
		App->renderer->Draw(background_dawn, 0, 0);
	}


	return UPDATE_CONTINUE;
}
