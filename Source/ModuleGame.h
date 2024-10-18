#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>
#include <set>

class PhysBody;
class PhysicEntity;


class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	std::vector<PhysicEntity*> entities;
	
	PhysBody* sensor;
	bool sensed;

	Texture2D circle;
	Texture2D box;
	Texture2D rick;

	uint32 bonus_fx;

	vec2<int> ray;
	bool ray_on;

	//TODO 1: Create a function in ModulePhysics that allows you to delete a PhysBody by calling DestroyBody on the world.

	//TODO 2: Expand the CreateCircle function to accept a mass, a radius and an initial velocity

	//TODO 3: When there are two collisions, check if both objects are circles...
	//		TIP: You can check their type by using dynamic_cast (not ideal), or creating a virtual function in PhysicEntity "IsCircle" and implementing it through polymorfism

	//TODO 4: If both objects are circles, remove them both and create a circle with the combined mass, radius (just sum both radius)

	//TODO 5: Set this new circle's velocity according to the conservation of momentum of both original circles (You'll need to get the info from theory...)
};
