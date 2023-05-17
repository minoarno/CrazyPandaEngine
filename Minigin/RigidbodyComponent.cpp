#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Log.h"

RigidbodyComponent::RigidbodyComponent(bool isStatic)
{
	m_BodyDef.type = (isStatic) ? b2_staticBody : b2_dynamicBody;
}

RigidbodyComponent::~RigidbodyComponent()
{
	b2World* pWorld = nullptr;// m_pGameObject->GetScene()->GetWorld();
	if (pWorld != nullptr)
	{
		if (pWorld->IsLocked())
		{
			ME_CORE_ERROR("Removal while physics step is active");
		}
		pWorld->DestroyBody(m_pBody);
	}
}

b2Fixture* RigidbodyComponent::AddCollider(const b2FixtureDef& )
{
	return nullptr;
}

void RigidbodyComponent::Move(const float , const float )
{
}

void RigidbodyComponent::Initialize()
{
}

void RigidbodyComponent::Update()
{
}