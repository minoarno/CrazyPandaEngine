#pragma once
#include "SceneManager.h"

class ContactListener;
class b2World;
class b2DebugDraw;
class RayCastCallback;
namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		GameObject* Add(GameObject* object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;
		void RenderImGui();
		
		void OnSceneDetach();
		void OnSceneAttach();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		b2World* GetWorld();
		bool RayCast(RayCastCallback& hit, const glm::vec2& pos, const glm::vec2& dir);
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<GameObject*> m_pObjects{};

		b2World* m_pWorld{ nullptr };
		ContactListener* m_pContactListener{ nullptr };
		b2DebugDraw* m_pB2DebugDraw{ nullptr };

		static unsigned int m_IdCounter; 
	};

}
