#pragma once

#include "Module.h"
#include "Globals.h"


// TODO 1: Include Box 2 header


// Module --------------------------------------
class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	

private:

	bool debug;
	
};