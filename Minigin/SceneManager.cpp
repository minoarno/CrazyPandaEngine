#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_Scenes[m_ActiveScene]->Update();
}

void dae::SceneManager::FixedUpdate()
{
	m_Scenes[m_ActiveScene]->FixedUpdate();
}

void dae::SceneManager::LateUpdate()
{
	m_Scenes[m_ActiveScene]->LateUpdate();
}

void dae::SceneManager::Render()
{
	m_Scenes[m_ActiveScene]->Render();
}

void dae::SceneManager::CleanUp()
{
	m_Scenes.clear();
}

void dae::SceneManager::RenderImGui()
{
	m_Scenes[m_ActiveScene]->RenderImGui();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
