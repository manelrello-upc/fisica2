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

	circle = LoadTexture("Assets/wheel.png"); 
	box = LoadTexture("Assets/crate.png");
	rick = LoadTexture("Assets/rick_head.png");

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
	// TODO 4: Move all creation of bodies on 1,2,3 key press here in the scene
	if (IsKeyPressed(KEY_ONE))
	{
		bodies.push_back(App->physics->CreateCircle(GetMouseX(), GetMouseY(), 25));
	}

	if (IsKeyPressed(KEY_TWO))
	{
		// TODO 1: When pressing 2, create a box on the mouse position
		// To have the box behave normally, set fixture's density to 1.0f
		App->physics->CreateRectangle(GetMouseX(), GetMouseY(), 20, 10);
	}

	if (IsKeyPressed(KEY_THREE))
	{
		// TODO 2: Create a chain shape using those vertices
		// remember to convert them from pixels to meters!

		int points[62] = {
	43, 0,
	74, 32,
	87, 5,
	94, 40,
	111, 33,
	104, 57,
	117, 67,
	108, 74,
	111, 81,
	108, 90,
	104, 93,
	110, 98,
	101, 105,
	102, 116,
	106, 122,
	99, 127,
	94, 138,
	85, 149,
	74, 148,
	56, 145,
	46, 132,
	32, 138,
	40, 125,
	23, 124,
	31, 113,
	10, 102,
	25, 91,
	0, 76,
	30, 62,
	12, 35,
	42, 39
		};


		App->physics->CreateChain(GetMouseX(), GetMouseY(), points, 62);
	}

	// TODO 6: Draw all the circles using "circle" texture

	for each (PhysBody* body in bodies)
	{
		int x, y;
		body->GetPosition(x, y);

		App->renderer->Draw(circle, x - circle.width * 0.5f, y - circle.height * 0.5f);
	}

	return UPDATE_CONTINUE;
}
