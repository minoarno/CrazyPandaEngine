#include "MiniginPCH.h"
#include "EnemyComponent.h"
#include "Scene.h"

#include "DigDugComponent.h"
#include "TextureComponent.h"
#include "BoxCollider.h"

#include "ScoreManager.h"
#include "GameStateManager.h"

EnemyComponent::EnemyComponent()
	: BaseComponent{ }
	, m_Direction{ 0,-1 }
	, m_PreviousPosition{ }
	, m_State{ EnemyState::Walk }
{
}

void EnemyComponent::SetEnemyState(EnemyState newState)
{
	if (m_State == newState) return;

	m_CurrentAnimationIndex = 0;

	m_State = newState;
	if (newState == EnemyState::Ghost)
	{
		m_pRigidBody->ResetVelocity();
		m_pColliderComponent->SetIsTrigger(true);
	}
	if (m_State == EnemyState::Ghost)
	{
		m_pRigidBody->ResetVelocity();
		m_pColliderComponent->SetIsTrigger(false);
	}

	UpdateTexture();
}

void EnemyComponent::SetIsLookingRight(bool value)
{
	m_LooksRight = value;
	UpdateTexture();
}

void EnemyComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([&](b2Fixture* , b2Fixture* pOtherFixture, b2Contact* , CollisionType )
		{
			if (m_State != EnemyState::Walk && m_State != EnemyState::Ghost)return;

			auto gameObject = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
			if (gameObject->GetTag() == "Player")
			{
				gameObject->GetComponent<DigDugComponent>()->SetState(DigDugComponent::CharacterState::Die);
			}

		});

	m_Direction = { 0,-1 };

	m_pTexture = m_pGameObject->GetComponent<dae::TextureComponent>();
	m_pRigidBody = m_pGameObject->GetComponent<RigidBody>();
	m_pColliderComponent = m_pGameObject->GetComponent<BoxCollider>();
}

void EnemyComponent::Update()
{
	if (m_HasToBeAddedToList)
	{
		GameStateManager::GetInstance().OnEnemySpawn();
		m_HasToBeAddedToList = false;
	}

	switch (m_State)
	{
	case EnemyState::Walk:
	default:
		Walk();
		break;
	case EnemyState::Crushed:
		Crushed();
		break;
	case EnemyState::Bloated:
		Bloated();
		break;
	case EnemyState::Ghost:
		Ghost();
		break;
	case EnemyState::Fire:
		Fire();
		break;
	}

	if (m_LastAnimationTime + m_AnimationDuration > Time::GetInstance().GetTotalSeconds()) return;

	m_CurrentAnimationIndex++;
	UpdateTexture();
}

void EnemyComponent::UpdateTexture()
{
	m_LastAnimationTime = static_cast<float>(Time::GetInstance().GetTotalSeconds());

	switch (m_State)
	{
	case EnemyState::Walk:
	default:
		m_CurrentAnimationIndex %= m_WalkAnimations;
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Ghost:
		m_CurrentAnimationIndex %= m_GhosstAnimations;
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 48.f + m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Crushed:
		if (m_CurrentAnimationIndex == m_DeadAnimations)
		{
			AddScore();
			GameStateManager::GetInstance().OnEnemyDead();
			m_pGameObject->GetScene()->Remove(m_pGameObject);
			return;
		}
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 32.f + m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Bloated:
		if (m_CurrentAnimationIndex == m_BloathAnimations)
		{
			AddScore();
			GameStateManager::GetInstance().OnEnemyDead();
			m_pGameObject->GetScene()->Remove(m_pGameObject);
			return;
		}
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 32.f });
		m_pTexture->SetSourceRect({ m_CurrentAnimationIndex * 26.f,16.f,26.f,26.f });
		break;
	}
}

void EnemyComponent::Walk()
{
	RayCastCallback hit{};
	hit.m_Tags = { "Level", "Border" };
	glm::vec2 pos = m_pGameObject->GetTransform()->GetWorldPosition() + glm::vec3{ 8 };

	float distance = 10.f;
	if (m_pGameObject->GetScene()->RayCast(hit, pos, m_Direction * glm::vec2{ distance }))
	{
		std::vector<glm::vec2> possibleNewDirections{};
		RayCastCallback hitRight{};
		hitRight.m_Tags = { "Level", "Border" };
		if (!m_pGameObject->GetScene()->RayCast(hitRight, pos, glm::vec2{ distance,0 }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ 1,0 });
		}
		RayCastCallback hitLeft{};
		hitLeft.m_Tags = { "Level", "Border" };
		if (!m_pGameObject->GetScene()->RayCast(hitLeft, pos, glm::vec2{ -distance, 0 }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ -1,0 });
		}
		RayCastCallback hitDown{};
		hitDown.m_Tags = { "Level", "Border" };
		if (!m_pGameObject->GetScene()->RayCast(hitDown, pos, glm::vec2{ 0, distance }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ 0, 1 });
		}
		RayCastCallback hitUp{};
		hitUp.m_Tags = { "Level", "Border" };
		if (!m_pGameObject->GetScene()->RayCast(hitUp, pos, glm::vec2{ 0, -distance }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ 0, -1 });
		}
		m_Direction = possibleNewDirections[std::rand() % int(possibleNewDirections.size())];
		if (m_Direction.x > 0.01f)
		{
			m_pTexture->SetIsFlipped(false);
		}
		else if (m_Direction.x < -0.01f)
		{
			m_pTexture->SetIsFlipped(true);
		}
	}

	if (pos == m_PreviousPosition)
	{
		SetEnemyState(EnemyState::Ghost);
	}

	float elapsed = static_cast<float>(Time::GetInstance().GetElapsedSeconds());
	auto v = m_pRigidBody->GetBody()->GetLinearVelocity();
	m_pRigidBody->Move(m_Direction.x * m_Speed * elapsed, m_Direction.y * m_Speed * elapsed);
	
	m_PreviousPosition = pos;
}

void EnemyComponent::Ghost()
{

}

void EnemyComponent::Bloated()
{
	m_pRigidBody->GetBody()->SetLinearVelocity({ 0,0 });
}

void EnemyComponent::Crushed()
{
}

void EnemyComponent::Fire()
{
	SetEnemyState(EnemyState::Walk);
}

void EnemyComponent::AddScore()
{
	auto y = m_pGameObject->GetTransform()->GetWorldPosition().y;
	ScoreManager::GetInstance().IncreaseScore(ScoreManager::GetInstance().GetHeightMultiplier(y) * 100);
}
