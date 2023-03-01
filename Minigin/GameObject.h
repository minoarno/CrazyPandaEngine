#pragma once
#include "Transform.h"
#include <typeindex>
#include <functional>

namespace dae
{
	class BaseComponent;
	class TextureComponent;
	class Scene;
	class GameObject final
	{
	public:
		void SetPosition(float x, float y, float z = 0.0f);
		void SetPosition(const Vector2f& pos);
		float GetRotation()const;

		GameObject();
		~GameObject() = default;
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

		template<typename T>
		std::enable_if_t<std::is_base_of_v<GameObject, T>, T*> AddChild(T* newChild)
		{
			AddChild_(newChild);
			return newChild;
		}

		void SetParent(GameObject* newParentObject);
		void RemoveChild(GameObject* childObject);

		template<typename T>
		std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> GetComponent() const;

		template<typename T>
		void SetComponent(std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> value);

		GameObject* GetParent() { return m_pParent; };
		GameObject* GetChild(int index);
		const std::vector<GameObject*>& GetChildren()const { return m_pChildren; };


		void SetActive(bool value) { m_IsActive = value; }
		bool GetActive()const { return m_IsActive; }

		Transform* GetTransform()const { return m_pTransform; }
	private:
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
		void LateUpdate();

		void AddComponent_(BaseComponent* newComponent);
	};

	template<typename T>
	inline std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> GameObject::GetComponent() const
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
	inline void GameObject::SetComponent(std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> value)
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
