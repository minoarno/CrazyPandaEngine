#include "MiniginPCH.h"
#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(const glm::vec3& pos)
	: BaseComponent{}
	, m_LocalPosition{pos}
	, m_WorldPosition{}
{
}

glm::vec3 dae::Transform::GetWorldPosition()const
{
	const GameObject* parent = m_pGameObject->GetParent();
	if (m_NeedUpdate && parent != nullptr)
	{
		m_WorldPosition = parent->GetTransform()->GetWorldPosition();
		m_NeedUpdate = false;
	}

	return m_LocalPosition + m_WorldPosition;
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;

	m_NeedUpdate = true;

	const auto childTransforms = m_pGameObject->GetComponentsInChildren<Transform>();
	for (const auto child_transform : childTransforms)
	{
		child_transform->m_NeedUpdate = true;
	}
}

void dae::Transform::SetRotation(float angle)
{
	m_Angle = angle;
}

void dae::Transform::Move(float x, float y, float z)
{
	m_LocalPosition.x += x;
	m_LocalPosition.y += y;
	m_LocalPosition.z += z;
}

void dae::Transform::Move(const glm::fvec3& move)
{
	m_LocalPosition += move;
}