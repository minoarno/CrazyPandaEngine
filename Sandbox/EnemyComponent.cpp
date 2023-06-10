#include "MiniginPCH.h"
#include "EnemyComponent.h"
#include "Scene.h"

#include "DigDugComponent.h"
#include "TextureComponent.h"

EnemyComponent::EnemyComponent()
	: BaseComponent{ }
	, m_Direction{ 0,-1 }
{
}

void EnemyComponent::SetEnemyState(EnemyState newState)
{
	if (m_State == newState) return;

	m_CurrentAnimationIndex = 0;
	switch (newState)
	{
	case EnemyState::Walk:
	default:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 0.f,0.f,16.f,16.f });
		break;
	case EnemyState::Ghost:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 96.f,0.f,16.f,16.f });
		break;
	case EnemyState::Fire:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 48.f,0.f,16.f,16.f });
		break;
	case EnemyState::Crushed:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 32.f,0.f,16.f,16.f });
		break;
	case EnemyState::Bloated:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 32.f });
		m_pTexture->SetSourceRect({ 0.f,16.f,32.f,32.f });
		break;
	}

	m_State = newState;
}

void EnemyComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([](b2Fixture* , b2Fixture* pOtherFixture, b2Contact* , CollisionType )
		{
			auto gameObject = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
			if (gameObject->GetTag() == "Player")
			{
				gameObject->GetComponent<DigDugComponent>()->SetState(DigDugComponent::CharacterState::Die);
			}

		});

	m_Direction = { 0,-1 };

	m_pTexture = m_pGameObject->GetComponent<dae::TextureComponent>();
}

void EnemyComponent::Update()
{
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
			m_pTexture->SetIsFlipped(true);
		}
		else if (m_Direction.x < -0.01f)
		{
			m_pTexture->SetIsFlipped(false);
		}
	}

	float elapsed = static_cast<float>(Time::GetInstance().GetElapsedSeconds());
	RigidBody* rigidBody = m_pGameObject->GetComponent<RigidBody>();
	auto v = rigidBody->GetBody()->GetLinearVelocity();
	rigidBody->Move(m_Direction.x * m_Speed * elapsed, m_Direction.y * m_Speed * elapsed);
}

void EnemyComponent::Ghost()
{
}

void EnemyComponent::Bloated()
{
	Log::Info("Bloated");
}

void EnemyComponent::Crushed()
{
}

void EnemyComponent::Fire()
{
}
