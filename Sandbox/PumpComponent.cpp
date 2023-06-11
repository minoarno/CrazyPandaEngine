#include "MiniginPCH.h"
#include "PumpComponent.h"
#include "EnemyComponent.h"
#include "FygarComponent.h"
#include "EngineTime.h"
#include "Scene.h"

PumpComponent::PumpComponent(DigDugComponent::CharacterDirection direction)
	: BaseComponent{}
	, m_CharacterDirection{ direction }
{
}

void PumpComponent::AttachToEnemy(EnemyComponent* pEnemy)
{
	if (m_pEnemy != nullptr) return;
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
	m_pEnemy = nullptr;
	m_pGameObject->AddCollisionCallback([&](b2Fixture*, b2Fixture* pOtherFixture, b2Contact*, CollisionType)
		{
			if (this->m_pEnemy == nullptr)
			{
				auto gameObject = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
				if (gameObject == nullptr || gameObject->GetIsMarkedForDelete()) return;

				if (gameObject->GetTag() == "Pooka")
				{
					AttachToEnemy(gameObject->GetComponent<EnemyComponent>());
				}
				else if (gameObject->GetTag() == "Fygar")
				{
					auto fygar = gameObject->GetComponent<FygarComponent>();
					fygar->SetPump(this);
					AttachToEnemy(fygar);
				}
			}
		});
}

void PumpComponent::Update()
{
	float totalTime = static_cast<float>(Time::GetInstance().GetTotalSeconds());
	if (m_StartPump + m_PumpTotal < totalTime)
	{
		m_pGameObject->GetScene()->Remove(m_pGameObject);
	}
}
