#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"


#include "Log.h"
#include "Box2D.h"
#include "ContactListener.h"
#include "b2DebugDraw.h"
#include "EngineTime.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

b2World* dae::Scene::GetWorld()
{
	return m_pWorld;
}

Scene::Scene(const std::string& name) 
	: m_name(name) 
	, m_objects{}
	, m_pWorld{new b2World{{0,0}}}
{
	m_pWorld->SetAllowSleeping(false);
	m_pContactListener = new ContactListener{};
	m_pWorld->SetContactListener(m_pContactListener);

#if _DEBUG
	m_pB2DebugDraw = new b2DebugDraw();

	//enable all of the bitflags
	uint32 bitflags = 0;
	bitflags += b2Draw::e_shapeBit;
	bitflags += b2Draw::e_jointBit;
	bitflags += b2Draw::e_aabbBit;
	bitflags += b2Draw::e_pairBit;
	bitflags += b2Draw::e_centerOfMassBit;

	m_pB2DebugDraw->SetFlags(bitflags);
	m_pWorld->SetDebugDraw(m_pB2DebugDraw);
#endif
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	m_pWorld->Step(float(Time::GetInstance().GetElapsedSeconds()), 10, 8);

	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void dae::Scene::LateUpdate()
{
	for (auto& object : m_objects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::RenderImGui()
{
	for (const auto& object : m_objects)
	{
		object->RenderImGui();
	}
}

dae::Scene::~Scene()
{
	delete m_pContactListener;
	m_pContactListener = nullptr;

	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_pB2DebugDraw;
	m_pB2DebugDraw = nullptr;
}

