#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>
#include "Timer.h"

class PhysBody;
class PhysicEntity;

class Circle
{
public:
	Circle(std::unique_ptr<PhysBody> i_body, float i_mass);
	Circle(Circle&& i_other);
	~Circle();

	float GetLifeTime() const;
	void Draw();
	void Update(float i_staticFricion, float i_dynamicFriction);

private:
	std::unique_ptr<PhysBody> m_body;
	Timer m_lifeTime;
	float mass;

};

class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();



public:

	Timer m_creationTimer;
	std::vector<Circle> m_circles;
	
	std::vector<float> m_staticFrictions = { 0.0f, 0.1f, 0.3f, 0.5f };
	std::vector<float> m_dynamicFrictions = {0.0f, 0.1f, 0.3f, 0.5f};
	int m_currentStaticFriction = 0;
	int m_currentDynamicFriction = 0;

	// TODO 1: Every second, create a circle at the leftmost side of the screen at a random height.
	// TIP: You can check (and maybe reuse) some previous Handout...
	
	// TODO 2: Apply an horizontal Force to each circle so it crosses the screen with constant acceleration. (NO GRAVITY to the bottom of the screen)

	// TODO 3: Assign a random weight to each circle (from 1Kg to 100Kg), and make them bigger (or smaller) depending on their weight.

	// TODO 4: Apply a friction to these circles (as if the game had a top view) while they cross the screen. 

	// TODO 5: With each left click, increase the STATIC friction coeficient. (At some point, reset it back to zero). Display it at the bottom of the screen.

	// TODO 6: With each right click, increase the DYNAMIC friction coeficient. (At some point, reset it back to zero). Display it at the bottom of the screen.

};
