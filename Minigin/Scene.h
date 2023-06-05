#pragma once
#include "SceneManager.h"

class ContactListener;
class b2World;
class b2DebugDraw;
namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;
		void RenderImGui();
		
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		b2World* GetWorld();
	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector<std::shared_ptr<GameObject>> m_objects{};
		std::vector<std::shared_ptr<GameObject>> m_pToBeDeletedObjects{};

		b2World* m_pWorld{ nullptr };
		ContactListener* m_pContactListener{ nullptr };
		b2DebugDraw* m_pB2DebugDraw{ nullptr };

		static unsigned int m_idCounter; 
	};

}
