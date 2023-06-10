#include "MiniginPCH.h"
#include "PumpComponent.h"
#include "EnemyComponent.h"
#include "EngineTime.h"
#include "Scene.h"

void PumpComponent::AttachToEnemy(EnemyComponent* pEnemy)
{
	if (pEnemy != nullptr) return;
	m_pEnemy = pEnemy;
	m_pEnemy->SetEnemyState(EnemyComponent::EnemyState::Bloated);
}

void PumpComponent::DetachEnemy()
{
	if (m_pEnemy != nullptr)
	{
		float totalTime = static_cast<float>(Time::GetInstance().GetTotalSeconds());
		if (m_StartPump + m_PumpTotal > totalTime)
		{
			m_pEnemy->SetEnemyState(EnemyComponent::EnemyState::Walk);
		}
	}
}

void PumpComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([&](b2Fixture*, b2Fixture* pOtherFixture, b2Contact*, CollisionType)
		{
			if (this->m_pEnemy == nullptr)
			{
				auto gameObject = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
				if (gameObject->GetTag() == "Enemy")
				{
					AttachToEnemy(gameObject->GetComponent<EnemyComponent>());
				}
			}
		});
}

void PumpComponent::Update()
{
	if (m_pEnemy != nullptr)
	{
		float totalTime = static_cast<float>(Time::GetInstance().GetTotalSeconds());
		if (m_StartPump + m_PumpTotal < totalTime)
		{
			m_pGameObject->GetScene()->Remove(m_pEnemy->GetGameObject());
			m_pEnemy = nullptr;
		}
	}
}
