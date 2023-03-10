#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::GameObject() : m_pTransform{ nullptr }
{
	m_pTransform = AddComponent(new Transform{});
}

dae::GameObject::~GameObject()
{
	for (const BaseComponent* baseComponent : m_pBaseComponents)
	{
		delete baseComponent;
		baseComponent = nullptr;
	}
	m_pBaseComponents.clear();

	for (const GameObject* child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
	m_pChildren.clear();
}

void dae::GameObject::Initialize()
{
	if (m_IsInitialized) return;

	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->BaseInitialize();
	}

	m_IsInitialized = true;
}

void dae::GameObject::FixedUpdate()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->FixedUpdate();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->FixedUpdate();
	}
}

void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Update();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->LateUpdate();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Render();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_pTransform->SetLocalPosition(x, y, z);
}

void dae::GameObject::SetPosition(const Vector2f& pos)
{
	SetPosition(float(pos.x), float(pos.y), 0.f);
}

float dae::GameObject::GetRotation() const
{
	return GetTransform()->GetRotation();
}

void dae::GameObject::AddComponent_(BaseComponent* newComponent)
{
	m_pBaseComponents.emplace_back(newComponent);
	newComponent->SetGameObject(this);
	newComponent->BaseInitialize();
}

dae::GameObject* dae::GameObject::AddChild(GameObject* child)
{
	if(child->SetParent(this))
	{
		m_pChildren.emplace_back(child);		
		return child;
	}
	return nullptr;
}

bool dae::GameObject::SetParent(GameObject* newParentObject)
{
	if (this->m_pParent != nullptr)
	{
		//Detach it
		std::cout << "The object already has a parent\n";
		return false;
	}

	if (this == newParentObject)
	{
		//LOGGER
		std::cout << "The gameobject and the child are the same!\n";
		return false;
	}

	GameObject* currentGameObject = newParentObject;
	while (currentGameObject->m_pParent != nullptr)
	{
		if (currentGameObject->m_pParent == this) return false;
		currentGameObject = currentGameObject->m_pParent;
	}

	m_pParent = newParentObject;
	return true;
}

void dae::GameObject::RemoveChild(GameObject* childObject)
{
	for (int i = static_cast<int>(m_pChildren.size()) - 1; i >= 0; i--)
	{
		if (m_pChildren[i] == childObject)
		{
			delete m_pChildren[i];
			m_pChildren[i] = nullptr;
			m_pChildren.erase(m_pChildren.begin() + i);
		}
	}
}

dae::GameObject* dae::GameObject::GetChild(int index) const
{
	if (index >= int(m_pChildren.size()))
	{
		return nullptr;
	}

	return m_pChildren[index];
}
