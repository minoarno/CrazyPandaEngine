#include "MiniginPCH.h"
#include "RockComponent.h"

#include "PookaComponent.h"
#include "FygarComponent.h"
#include "DigDugComponent.h"

#include "Scene.h"
#include "EngineTime.h"
#include "TextureComponent.h"

void RockComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([&](b2Fixture*, b2Fixture* pOtherFixture, b2Contact*, CollisionType)
		{
			if (m_IsFalling)
			{
				auto gameObject = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
				if (gameObject->GetTag() == "Pooka")
				{
					//Kill enemy
					EnemyComponent* pEnemy = gameObject->GetComponent<PookaComponent>();
					pEnemy->SetEnemyState(EnemyComponent::EnemyState::Crushed);
				}
				if (gameObject->GetTag() == "Fygar")
				{
					//Kill enemy
					EnemyComponent* pEnemy = gameObject->GetComponent<FygarComponent>();
					pEnemy->SetEnemyState(EnemyComponent::EnemyState::Crushed);
				}
				if (gameObject->GetTag() == "Player")
				{
					//Kill player
					DigDugComponent* pDigDug = gameObject->GetComponent<DigDugComponent>();
					pDigDug->SetState(DigDugComponent::CharacterState::Crushed);
				}
			}
		});

	m_pTextureComponent = m_pGameObject->GetComponent<dae::TextureComponent>();
	m_pTextureComponent->SetSourceRect({ m_AnimationIndex * 16.f,0.f,16.f,16.f });
}

void RockComponent::Update()
{
	if (m_IsCrumbling)
	{
		if (m_SmallStartCrumble + m_SmallCrumbleDuration < Time::GetInstance().GetTotalSeconds())
		{
			m_AnimationIndex++;
			if (m_AnimationIndex == 4)
			{
				m_pGameObject->GetScene()->Remove(m_pGameObject);
				return;
			}
			m_pTextureComponent->SetSourceRect({ m_AnimationIndex * 16.f,0.f,16.f,16.f });
			m_SmallStartCrumble = static_cast<float>(Time::GetInstance().GetTotalSeconds());
		}

		return;
	}

	glm::vec2 pos = m_pGameObject->GetTransform()->GetWorldPosition() + glm::vec3{ 10 };

	if (!m_IsFalling)
	{
		RayCastCallback hitDown{};
		hitDown.m_Tags = { "Level", "Border", "Player"};
		if (!m_pGameObject->GetScene()->RayCast(hitDown, pos, glm::vec2{ 0, 12 }))
		{
			m_StartWobble = static_cast<float>(Time::GetInstance().GetTotalSeconds());
			m_IsFalling = true;
		}
		return;
	}
	
	if (m_StartWobble + m_WobbleDuration > Time::GetInstance().GetTotalSeconds()) return;
	
	m_pGameObject->GetComponent<RigidBody>()->GetBody()->SetGravityScale(1);

	RayCastCallback hitGround{};
	hitGround.m_Tags = { "Level", "Border" };
	if (m_pGameObject->GetScene()->RayCast(hitGround, pos, glm::vec2{ 0, 12 }))
	{
		m_IsCrumbling = true;
		m_SmallStartCrumble = static_cast<float>(Time::GetInstance().GetTotalSeconds());
		m_AnimationIndex++;
		m_pTextureComponent->SetSourceRect({ m_AnimationIndex * 16.f,0.f,16.f,16.f });
	}
}
