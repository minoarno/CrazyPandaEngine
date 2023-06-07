#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Log.h"

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

void dae::SceneManager::NextScene()
{
	if (m_Scenes.size() > 1)
	{
		m_Scenes[m_ActiveScene]->OnSceneDetach();
		m_ActiveScene = ++m_ActiveScene % m_Scenes.size();
		m_Scenes[m_ActiveScene]->OnSceneAttach();
	}
}

void dae::SceneManager::LoadScene(int index)
{
	if (index != m_ActiveScene)
	{
		if (index >= 0 && index < int(m_Scenes.size()))
		{
			m_Scenes[m_ActiveScene]->OnSceneDetach();
			m_ActiveScene = index;
			m_Scenes[m_ActiveScene]->OnSceneAttach();
		}
		else
		{
			// out of range
			ME_CORE_WARN("The scene index is out of range");
		}
	}
	else
	{
		// Same scene
		ME_CORE_WARN("The scene is the same as the current one");
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
