#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();

		void CleanUp();
		void RenderImGui();
		void RenderDebug();

		void NextScene();
		void LoadScene(int index);
		void LoadScene(const std::string& name);

		Scene& GetActiveScene()const;
		int GetActiveSceneIndex()const { return m_ActiveScene; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveScene = 0;
	};
}
