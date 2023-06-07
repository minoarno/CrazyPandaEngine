#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"


#include "Log.h"
#include "Box2D.h"
#include "ContactListener.h"
#include "b2DebugDraw.h"
#include "EngineTime.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

b2World* dae::Scene::GetWorld()
{
	return m_pWorld;
}

Scene::Scene(const std::string& name) 
	: m_Name(name) 
	, m_pObjects{}
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

GameObject* Scene::Add(GameObject* pObject)
{
	pObject->SetScene(this);
	m_pObjects.emplace_back(std::move(pObject));
	return m_pObjects.back();
}

void Scene::Remove(GameObject* object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	m_pWorld->Step(float(Time::GetInstance().GetElapsedSeconds()), 10, 8);

	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->FixedUpdate();
	}
}

void dae::Scene::LateUpdate()
{
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->LateUpdate();
	}
}

void Scene::Render() const
{
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->Render();
	}
}

void Scene::RenderImGui()
{
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->RenderImGui();
	}
}

void dae::Scene::OnSceneDetach()
{
}

void dae::Scene::OnSceneAttach()
{
}

dae::Scene::~Scene()
{
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		delete m_pObjects[i];
		m_pObjects[i] = nullptr;
	}
	m_pObjects.clear();

	delete m_pContactListener;
	m_pContactListener = nullptr;

	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_pB2DebugDraw;
	m_pB2DebugDraw = nullptr;
}

