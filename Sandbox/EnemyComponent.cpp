#include "MiniginPCH.h"
#include "EnemyComponent.h"

EnemyComponent::EnemyComponent()
{
}

void EnemyComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([](b2Fixture* pThisFixture, b2Fixture* pOtherFixture, b2Contact* pContact, CollisionType contactType)
		{
			auto userData = pOtherFixture->GetUserData();
			if ()
			{

			}
		});
}

void EnemyComponent::Update()
{
}
