#include "MiniginPCH.h"
#include <string>
#include "GameObject.h"
#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::GameObject()
	:m_pTransform{ new Transform{} }
{
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
}

void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_pTransform->SetPosition(x, y, z);
}

void dae::GameObject::SetPosition(const Vector2f& pos)
{
	SetPosition(float(pos.x), float(pos.y), 0.f);
}

Vector2f dae::GameObject::GetPosition() const
{
	auto pos = m_pTransform->GetPosition();

	return Vector2f(pos.x,pos.y);
}

void dae::GameObject::AddComponent_(BaseComponent* newComponent)
{
	m_pBaseComponents.emplace_back(newComponent);
	newComponent->SetGameObject(this);
	newComponent->BaseInitialize();
}
