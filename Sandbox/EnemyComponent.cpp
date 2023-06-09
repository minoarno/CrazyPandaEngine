#include "MiniginPCH.h"
#include "EnemyComponent.h"
#include "Scene.h"

EnemyComponent::EnemyComponent()
	: BaseComponent{ }
	, m_Direction{ 0,-1 }
{
}

void EnemyComponent::SetEnemyState(EnemyState newState)
{
	if (m_State == newState) return;



	m_State = newState;
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

	m_Direction = { 0,-1 };
}

void EnemyComponent::Update()
{
	switch (m_State)
	{
	case EnemyState::Walk:
	case EnemyState::Die:
	case EnemyState::Bloated:
	case EnemyState::Ghost:
	case EnemyState::Fire:
	default:
		break;
	}

	RayCastCallback hit{};
	hit.m_Tag = "Level";
	glm::vec2 pos = m_pGameObject->GetTransform()->GetWorldPosition() + glm::vec3{ 8 };

	float distance = 10.f;
	if (m_pGameObject->GetScene()->RayCast(hit, pos, m_Direction * glm::vec2{ distance }))
	{
		std::vector<glm::vec2> possibleNewDirections{};
		RayCastCallback hitRight{};
		if (!m_pGameObject->GetScene()->RayCast(hitRight, pos, glm::vec2{ distance,0 }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ 1,0 });
		}
		RayCastCallback hitLeft{};
		if (!m_pGameObject->GetScene()->RayCast(hitLeft, pos, glm::vec2{ -distance, 0 }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ -1,0 });
		}
		RayCastCallback hitDown{};
		if (!m_pGameObject->GetScene()->RayCast(hitDown, pos, glm::vec2{ 0, distance }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ 0, 1 });
		}
		RayCastCallback hitUp{};
		if (!m_pGameObject->GetScene()->RayCast(hitUp, pos, glm::vec2{ 0, -distance }))
		{
			possibleNewDirections.emplace_back(glm::vec2{ 0, -1 });
		}
		m_Direction = possibleNewDirections[std::rand() % possibleNewDirections.size()];
	}
	float elapsed = static_cast<float>(Time::GetInstance().GetElapsedSeconds());
	RigidBody* rigidBody = m_pGameObject->GetComponent<RigidBody>();
	auto v = rigidBody->GetBody()->GetLinearVelocity();
	rigidBody->Move(m_Direction.x * m_Speed * elapsed, m_Direction.y * m_Speed * elapsed);
}
