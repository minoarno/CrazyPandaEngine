#include "MiniginPCH.h"
#include "DigDugComponent.h"
#include "Scene.h"
#include "PrefabFactoryClass.h"
#include "TextureComponent.h"
#include "Lives.h"

DigDugComponent::DigDugComponent()
{
}

void DigDugComponent::PumpAttack()
{
	auto pos = m_pGameObject->GetTransform()->GetWorldPosition();
	switch (m_Direction)
	{
	case CharacterDirection::Down:
		pos.y += 16;
		break;
	case CharacterDirection::Up:
		pos.y -= 32;
		break;
	case CharacterDirection::Left:
		pos.x -= 32;
		break;
	case CharacterDirection::Right:
	default:
		pos.x += 16;
		break;
	}

	CreatePump(*m_pGameObject->GetScene(),{pos.x,pos.y}, {32,32}, int(m_Direction));
}

void DigDugComponent::SetDirection(CharacterDirection direction)
{
	m_Direction = direction;
	UpdateTexture();
}

void DigDugComponent::SetState(CharacterState state)
{
	if (m_State == state)return;

	m_State = state;
	m_CurrentAnimationIndex = 0;
	UpdateTexture();
}

void DigDugComponent::SetRespawn(const glm::vec2& pos)
{
	m_RespawnPosition = pos;
}

void DigDugComponent::Respawn()
{
	SetState(CharacterState::Walk);
	SetDirection(CharacterDirection::Right);

	m_pGameObject->SetPosition(m_RespawnPosition);
	m_pGameObject->GetComponent<RigidBody>()->ResetVelocity();
	m_pGameObject->GetComponent<Lives>()->LoseLife();
}

void DigDugComponent::Initialize()
{
	m_pTexture = m_pGameObject->GetComponent<dae::TextureComponent>();
}

void DigDugComponent::Update()
{
	if (m_LastAnimationTime + m_AnimationDuration > Time::GetInstance().GetTotalSeconds()) return;

	m_CurrentAnimationIndex++;
	UpdateTexture();
}

void DigDugComponent::UpdateTexture()
{
	m_LastAnimationTime = static_cast<float>(Time::GetInstance().GetTotalSeconds());

	int directionIndex{ int(m_Direction) };
	switch (m_State)
	{
	case CharacterState::Walk:
		m_CurrentAnimationIndex %= m_WalkAnimations;
		m_pTexture->SetSourceRect({ (directionIndex * m_WalkAnimations + m_CurrentAnimationIndex) * 16.f, 0.f,16.f,16.f });
		break;
	case CharacterState::Crushed:
		if (m_CurrentAnimationIndex == m_GetCrushedAnimations)
		{
			Respawn();
			return;
		}
		m_CurrentAnimationIndex %= m_GetCrushedAnimations;
		m_pTexture->SetSourceRect({ (directionIndex * m_GetCrushedAnimations + m_CurrentAnimationIndex) * 16.f, 16.f,16.f,16.f });
	case CharacterState::Die:
		if (m_CurrentAnimationIndex == m_DeadAnimations)
		{
			Respawn();
			return;
		}
		m_CurrentAnimationIndex %= m_DeadAnimations;
		m_pTexture->SetSourceRect({ (directionIndex * m_DeadAnimations + m_CurrentAnimationIndex) * 16.f, 32.f,16.f,16.f });
	default:
		break;
	}
}
