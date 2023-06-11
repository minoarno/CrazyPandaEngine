#include "MiniginPCH.h"
#include "FygarComponent.h"

#include "TextureComponent.h"
#include "Scene.h"

#include "ScoreManager.h"
#include "GameStateManager.h"

FygarComponent::FygarComponent()
	: EnemyComponent{}
{
}

void FygarComponent::UpdateTexture()
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
		m_pTexture->SetSourceRect({ 96.f + m_CurrentAnimationIndex * 16.f,0.f,16.f,16.f });
		break;
	case EnemyState::Fire:
		m_CurrentAnimationIndex %= m_WalkAnimations;
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

void FygarComponent::AddScore()
{
	auto y = m_pGameObject->GetTransform()->GetWorldPosition().y;
	if (m_pPump != nullptr
		&& (m_pPump->GetCharacterDirection() == DigDugComponent::CharacterDirection::Left
		|| m_pPump->GetCharacterDirection() == DigDugComponent::CharacterDirection::Right))
	{
		ScoreManager::GetInstance().IncreaseScore(ScoreManager::GetInstance().GetHeightMultiplier(y) * 200);
	}
	else
	{
		ScoreManager::GetInstance().IncreaseScore(ScoreManager::GetInstance().GetHeightMultiplier(y) * 100);
	}
}

void FygarComponent::Fire()
{

}
