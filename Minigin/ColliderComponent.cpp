#include "MiniginPCH.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent()
	:BaseComponent{}
{
}

void ColliderComponent::SetIsTrigger(bool value)
{
	m_pFixture->SetSensor(value);
}

void ColliderComponent::Initialize()
{
	m_FixtureDef.shape = &m_Shape;
	m_FixtureDef.filter = m_Filter;
	m_FixtureDef.density = 1.f;
	m_FixtureDef.friction = 0.f;

	RigidBody* pRigid = m_pGameObject->GetComponent<RigidBody>();
	if (pRigid == nullptr)
	{
		Log::CoreWarning("You need to add the rigidbody before the collider component.");
		return;
	}
	m_pFixture = pRigid->AddCollider(m_FixtureDef);
	m_pFixture->SetUserData(this->m_pGameObject);
}
