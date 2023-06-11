#include "MiniginPCH.h"
#include "FygarComponent.h"

#include "TextureComponent.h"
#include "Scene.h"

#include "ScoreManager.h"

FygarComponent::FygarComponent()
	: EnemyComponent{}
{
}

void FygarComponent::Initialize()
{
	EnemyComponent::Initialize();
	auto pTexture = m_pGameObject->AddComponent(new dae::TextureComponent{ "Fygar.png" });
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });
}

void FygarComponent::UpdateTexture()
{
	switch (m_State)
	{
	case EnemyState::Walk:
	default:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Ghost:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 96.f + m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Fire:
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 48.f + m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Crushed:
		if (m_CurrentAnimationIndex == m_DeadAnimations)
		{
			m_pGameObject->GetScene()->Remove(m_pGameObject);
			return;
		}
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 16.f });
		m_pTexture->SetSourceRect({ 32.f + m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Bloated:
		if (m_CurrentAnimationIndex == m_BloathAnimations)
		{
			m_pGameObject->GetScene()->Remove(m_pGameObject);
			return;
		}
		m_pTexture->SetDestinationRectDimensions(glm::vec2{ 32.f });
		m_pTexture->SetSourceRect({ m_CurrentAnimationIndex * 26.f,16.f,26.f,26.f });
		break;
	}
}

void FygarComponent::AddScore()
{
	if (m_pPump != nullptr &&
		(m_pPump->GetCharacterDirection() == DigDugComponent::CharacterDirection::Left ||
		m_pPump->GetCharacterDirection() == DigDugComponent::CharacterDirection::Right))
	{
		ScoreManager::GetInstance().IncreaseScore(ScoreManager::GetInstance().GetHeightMultiplier(200));
	}
	else
	{
		ScoreManager::GetInstance().IncreaseScore(ScoreManager::GetInstance().GetHeightMultiplier(100));
	}
}

void FygarComponent::Fire()
{

}
