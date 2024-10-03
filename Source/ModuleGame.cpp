#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include <cmath>
#include <format>

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
	m_creationTimer.Start();
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
	if (m_creationTimer.ReadSec() > 1.0f)
	{
		float mass = std::rand() % 19 + 1;
		m_creationTimer.Start();
		int y = std::rand() % 400;
		std::unique_ptr<PhysBody> circleBody = App->physics->CreateCircle(0, y, 10 * std::log(mass));
		m_circles.emplace_back(std::move(circleBody), mass);
	}

	if (IsMouseButtonPressed(0))
	{
		m_currentStaticFriction = (m_currentStaticFriction + 1 ) % m_staticFrictions.size();
	}
	
	if (IsMouseButtonPressed(1))
	{
		m_currentDynamicFriction = (m_currentDynamicFriction + 1) % m_dynamicFrictions.size();
	}

	DrawText(std::format("{}/ {}", m_staticFrictions[m_currentStaticFriction], m_dynamicFrictions[m_currentDynamicFriction]).c_str(), 10, 600, 30, BLACK);

	for (Circle& c : m_circles)
	{
		c.Update(m_staticFrictions[m_currentStaticFriction], m_dynamicFrictions[m_currentDynamicFriction]);
	}

	for (Circle& c : m_circles)
	{
		c.Draw();
	}

	return UPDATE_CONTINUE;
}

Circle::Circle(std::unique_ptr<PhysBody> i_body, float i_mass)
	: m_body(std::move(i_body))
	, mass(i_mass)
{
	m_lifeTime.Start();
}

Circle::Circle(Circle&& i_other)
	: m_body(std::move(i_other.m_body))
	, mass(i_other.mass)
{
}

Circle::~Circle()
{
}

float Circle::GetLifeTime() const
{
	return m_lifeTime.ReadSec();
}

void Circle::Draw()
{
	b2Vec2 pos = m_body->body->GetPosition();
	DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), (float)METERS_TO_PIXELS(std::log(mass)), Color{ 128, 0, 0, 128 });

}

void Circle::Update(float i_staticFricion, float i_dynamicFriction)
{
	float forceX = 20.0f;
	if (m_body->body->GetLinearVelocity().LengthSquared() < 0.001f)
	{
		float N = mass * 9.8f;
		float staticFriction = N * i_staticFricion;
		forceX = std::max(0.0f, forceX - staticFriction);
	}
	else
	{
		float N = mass * 9.8f;
		float dynamicFriction = N * i_dynamicFriction;
		forceX = std::max(0.0f, forceX - dynamicFriction);
	}
	float dynamicFrictionCoed = 0.5f;
	m_body->body->ApplyForce(b2Vec2(forceX, 0.0f), b2Vec2_zero, true);
}
