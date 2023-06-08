#include "MiniginPCH.h"
#include "EnemyComponent.h"
#include "Scene.h"

EnemyComponent::EnemyComponent()
{
}

void EnemyComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([](b2Fixture* , b2Fixture* pOtherFixture, b2Contact* , CollisionType )
		{
			auto gameObject = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
			if (gameObject->GetTag() == "Player")
			{
				Log::Info("Hit a player");
			}
		});
}

void EnemyComponent::Update()
{
	RayCastCallback hit{}, hit2{}, hit3{}, hit4{};
	glm::vec2 pos = m_pGameObject->GetTransform()->GetWorldPosition();

	if (m_pGameObject->GetScene()->RayCast(hit, pos, { 1,0 }))
	{
		Log::Info("Hit");
	}

	if (m_pGameObject->GetScene()->RayCast(hit2, pos, { -1,0 }))
	{
		Log::Info("Hit");
	}

	if (m_pGameObject->GetScene()->RayCast(hit3, pos, { 0, 1 }))
	{
		Log::Info("Hit");
	}

	if (m_pGameObject->GetScene()->RayCast(hit4, pos, { 0, -1 }))
	{
		Log::Info("Hit");
	}
}
