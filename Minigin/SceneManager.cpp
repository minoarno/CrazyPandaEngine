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

void dae::SceneManager::RenderDebug()
{
	m_Scenes[m_ActiveScene]->RenderDebug();
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
			Log::CoreWarning("The scene index is out of range");
		}
	}
	else
	{
		// Same scene
		Log::CoreWarning("The scene is the same as the current one");
	}
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	for (int index = 0; index < m_Scenes.size(); index++)
	{
		if (m_Scenes[index].get()->GetSceneName() == name)
		{
			m_Scenes[m_ActiveScene]->OnSceneDetach();
			m_ActiveScene = index;
			m_Scenes[m_ActiveScene]->OnSceneAttach();
			return;
		}
	}
	Log::CoreWarning("The scene with name \"" + name + "\" has not been found. Old scene remains.");
}

dae::Scene& dae::SceneManager::GetActiveScene() const
{
	return *m_Scenes[m_ActiveScene];
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
