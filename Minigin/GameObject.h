#pragma once
#include "Transform.h"
#include <typeindex>
#include <functional>

enum class CollisionType
{
	BeginContact,
	EndContact,
	PreSolve,
	PostSolve
};

class b2Fixture;
class b2Contact;
typedef std::function<void(b2Fixture*, b2Fixture*, b2Contact*, CollisionType)> CollisionCallback;
namespace dae
{
	class BaseComponent;
	class TextureComponent;
	class Scene;
	class GameObject final
	{
	public:
		void SetPosition(float x, float y, float z = 0.0f);
		void SetPosition(const glm::vec2& pos);
		[[nodiscard]] float GetRotation()const;

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename T>
		std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> AddComponent(T* newComponent)
		{
			AddComponent_(newComponent);
			return newComponent;
		}

		GameObject* AddChild(GameObject* child);
		
		bool SetParent(GameObject* newParentObject);
		void RemoveChild(GameObject* childObject);

		void SetScene(Scene* pScene);
		[[nodiscard]] Scene* GetScene() const;

		template<typename T>
		[[nodiscard]] std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> GetComponent() const;
		template<typename T>
		[[nodiscard]] std::enable_if_t<std::is_base_of_v<BaseComponent, T>, std::vector<T*>> GetComponentsInChildren() const;

		template<typename T>
		void SetComponent(std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> value);

		[[nodiscard]] GameObject* GetParent() const { return m_pParent; };
		GameObject* GetChild(int index) const;
		[[nodiscard]] const std::vector<GameObject*>& GetChildren()const { return m_pChildren; };

		void SetActive(bool value) { m_IsActive = value; }
		[[nodiscard]] bool GetActive()const { return m_IsActive; }

		[[nodiscard]] Transform* GetTransform()const { return m_pTransform; }

		void Collision(b2Fixture* pThisFixture, b2Fixture* pOtherFixture, b2Contact* pContact, CollisionType contactType);
		void AddCollisionCallback(const CollisionCallback& callback);
	private:
		dae::Scene* m_pScene;
		std::string m_Tag;

		bool m_IsActive{ true };
		bool m_IsInitialized{ false };
		
		Transform* m_pTransform;
		std::vector<BaseComponent*> m_pBaseComponents;
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent = nullptr;

		friend class Scene;

		void Initialize();
		void Update();
		void FixedUpdate();
		void Render()const;
		void RenderImGui();
		void LateUpdate();

		void AddComponent_(BaseComponent* newComponent);

		std::vector<CollisionCallback> m_CollisionCallbacks;
	};

	template<typename T>
	std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> GameObject::GetComponent() const
	{
		for (BaseComponent* c : m_pBaseComponents)
		{
			if (typeid(T).name() == typeid(*c).name())
			{
				return reinterpret_cast<T*>(c);
			}
		}
		return nullptr;
	}

	template<typename T>
	std::enable_if_t<std::is_base_of_v<BaseComponent, T>, std::vector<T*>> GameObject::GetComponentsInChildren() const
	{
		std::vector<T*> componentsInChildren = std::vector<T*>(); 

		for(GameObject* child : m_pChildren)
		{
			T* component = child->GetComponent<T>();
			if (component == nullptr)continue;

			componentsInChildren.emplace_back(component);

			auto childOfChildren = child->GetComponentsInChildren<T>();
			componentsInChildren.insert(componentsInChildren.end(),childOfChildren.begin(),childOfChildren.end());
		}

		return componentsInChildren;
	}

	template<typename T>
	void GameObject::SetComponent(std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> value)
	{
		for (BaseComponent*& c : m_pBaseComponents)
		{
			if (typeid(T) == typeid(*c))
			{
				delete c;
				c = reinterpret_cast<BaseComponent*>(value);
				return;
			}
		}
	}
}
