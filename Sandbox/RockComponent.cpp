#include "MiniginPCH.h"
#include "RockComponent.h"

#include "FygarComponent.h"
#include "DigDugComponent.h"

#include "Scene.h"
#include "EngineTime.h"
#include "TextureComponent.h"

#include "ScoreManager.h"

void RockComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([&](b2Fixture*, b2Fixture* pOtherFixture, b2Contact*, CollisionType)
		{
			if (m_IsFalling)
			{
				auto gameObject = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
				if (gameObject->GetTag() == "Pooka")
				{
					if (gameObject->GetIsMarkedForDelete()) return;
					m_AmountOfEnemiesCrushed++;

					//Kill enemy
					EnemyComponent* pEnemy = gameObject->GetComponent<EnemyComponent>();
					pEnemy->SetEnemyState(EnemyComponent::EnemyState::Crushed);
				}
				if (gameObject->GetTag() == "Fygar")
				{
					if (gameObject->GetIsMarkedForDelete()) return;
					m_AmountOfEnemiesCrushed++;

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
				GivePointsForCrushingEnemies();

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

void RockComponent::GivePointsForCrushingEnemies()
{
	int addedScore{ 0 };

	switch (m_AmountOfEnemiesCrushed)
	{
	default:
	case 0:
		addedScore = 0;
		break;
	case 1:
		addedScore = 1000;
		break;
	case 2:
		addedScore = 2500;
		break;
	case 3:
		addedScore = 4000;
		break;
	case 4:
		addedScore = 6000;
		break;
	case 5:
		addedScore = 8000;
		break;
	case 6:
		addedScore = 10000;
		break;
	case 7:
		addedScore = 12000;
		break;
	case 8:
		addedScore = 15000;
		break;
	}

	ScoreManager::GetInstance().IncreaseScore(addedScore);
}
